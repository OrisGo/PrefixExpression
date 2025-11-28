#include "ExprStruct.h"
#include <stack>
#include <stdexcept>

double evaluate(char P, double val1, double val2)
{
    double ans = 0;
    switch(P)
    {
    case '+':
        ans = val1 + val2;
        break;
    case '-':
        ans = val1 - val2;
        break;
    case '*':
        ans = val1 * val2;
        break;
    case '/':
        ans = val1 / val2;
        break;
    case '^':
        ans = pow(val1,val2);
        break;
    }
    return ans;
}

Node::Node(char P, bool isOperator)
{
    isOperand = !isOperator;

    c = P;

    if(isOperator)
    {
        existVar = false;
    } else if('0' <= P && P <= '9')
    {
        existVar = false;
        val = static_cast<double>(P - '0');
    } else if('a' <= P && P <= 'z')
    {
        existVar = true;
    }
}


Expr::Expr(const Expr& other):existVar(other.existVar),prefix(other.prefix)
{
    varMap = other.varMap;
    this->root = clone(other.root);
}


Expr& Expr::operator=(const Expr& other)
{
    if(this != &other)
    {
        Node* newNode = clone(other.root);
        destroy(this->root);


        this->root = newNode;


        this->varMap = other.varMap;
        prefix = other.prefix;
        this->existVar = other.existVar;
    }
    return *this;
}


Expr::~Expr()
{
    destroy(root);
}


QString Expr::toInfix() const
{
    QString ans = toInfix(root);
    return ans;
}


void Expr::setVarValue(char c,int v){
    varMap[c] = v;
}


double Expr::value()
{
    return evaluate(root);
}


QString Expr::toInfix(Node* root) const
{
    if(!root) return "";
    if(root->isOperand) return QString(root->c);

    QString ans = "";

    const std::unordered_map<char,int> priority = {{'+',1},{'-',1},{'*',2},{'/',2},{'^',3}};

    QString L = toInfix(root->left);
    QString R = toInfix(root->right);

    int P_parent = priority.at(root->c);


    // === 左子树加括号判断 ===
    bool leftBracket = false;
    if (!root->left->isOperand)
    {
        int P_left = priority.at(root->left->c);

        // 条件1: 父节点优先级高于左子节点优先级
        if (P_parent > P_left) {
            leftBracket = true;
        }
        // 条件2: 父节点和左子节点优先级相等，且是右结合运算符 (^)
        else if (P_parent == P_left && root->c == '^') {
            leftBracket = true;
        }
    }

    // 组合左子树部分
    if (leftBracket) ans += "(";
    ans += L;
    if (leftBracket) ans += ")";

    // 插入父节点运算符
    ans += root->c;

    // === 右子树加括号判断 ===
    bool rightBracket = false;
    if (!root->right->isOperand)
    {
        int P_right = priority.at(root->right->c);

        // 条件1: 父节点优先级高于右子节点优先级
        if (P_parent > P_right) {
            rightBracket = true;
        }
        // 条件2: 父节点和右子节点优先级相等，且是左结合运算符 (+, -, *, /)
        // 排除右结合运算符 (^)
        else if (P_parent == P_right && root->c != '^') {
            rightBracket = true;
        }
    }

    // 组合右子树部分
    if (rightBracket) ans += "(";
    ans += R;
    if (rightBracket) ans += ")";

    return ans;
}


double Expr::evaluate(Node* root)
{
    if(root->isOperand)
    {
        if(!('0'<= root->c && root->c <= '9')) root->val = varMap[root->c];
        return root->val;
    }

    double left = this->evaluate(root->left);
    double right = this->evaluate(root->right);

    char c = root->c;

    if(c == '/' && right == 0) throw std::runtime_error("除数出现0，请检查表达式");

    double ans = ::evaluate(c,left,right);

    return ans;
}


Node* Expr::clone(const Node* other)
{
    if(!other)
    {
        return nullptr;
    }

    Node* newNode = new Node((*other).c,!(*other).isOperand);
    newNode->left = clone(other->left);
    newNode->right = clone(other->right);

    newNode->val = other->val;
    newNode->existVar = other->existVar;
    return newNode;
}


bool validPrefix(QString s)
{
    std::stack<double> stk;
    std::stack<bool> Var;
    for(int i = s.length()-1; i >= 0; --i)
    {
        char c = s.at(i).toLatin1();

        if(isOperator(c))
        {
            if(stk.size() < 2) return false;
            double left = stk.top();
            bool leftVar = Var.top();
            stk.pop();
            Var.pop();
            double right = stk.top();
            bool rightVar = Var.top();
            stk.pop();
            Var.pop();

            if(c == '/' && !rightVar && right == 0) return false;

            double res = 0;

            if(!leftVar && !rightVar)
            {
                res = evaluate(c,left,right);
            }
            stk.push(res);

            Var.push(leftVar || rightVar);
        } else {
            // 若为变量则初始为0
            double val = 0;

            bool isCurrentVar = false;

            if('0' <= c && c <= '9')
            {
                val = static_cast<double> (c - '0');
            }
            else if('a' <= c && c <= 'z')
            {
                val = 0;
                isCurrentVar = true;
            }
            else
            {
                return false;
            }
            stk.push(val);

            Var.push(isCurrentVar);
        }

    }

    return stk.size() == 1 && Var.size() == 1;
}


Expr createExpr(QString prefix)
{
    /*
     *由一个合法的波兰表达式转为二叉树存储
     */
    Expr ans;
    ans.prefix = prefix;

    std::stack<Node*> s;
    for(int i = prefix.length()-1; i >= 0; i--)
    {
        QChar P = prefix.at(i);
        char c = P.toLatin1();

        if(isOperator(c))
        {
            Node* leftNode = s.top();
            s.pop();
            Node* rightNode = s.top();
            s.pop();

            Node* newNode = new Node(c);
            newNode->left = leftNode;
            newNode->right = rightNode;

            newNode->existVar = leftNode->existVar || rightNode->existVar;

            if (!newNode->existVar) {
                newNode->val = evaluate(c, leftNode->val, rightNode->val);
            } else {
                ans.existVar = true;
            }

            s.push(newNode);
        } else {
            Node* newNode = new Node(c,false);

            if(newNode->existVar)
            {
                ans.varMap[c] = 0;
                ans.existVar = true;
            }

            s.push(newNode);
        }
    }

    if(s.size() == 1)
    {
        ans.root = s.top();
        s.pop();
    }
    else
    {
        qDebug() << "波兰表达式转化失败";
        while(!s.empty())
        {
            Node* toClearNode = s.top();
            s.pop();
            destroy(toClearNode);
        }
    }
    return ans;
}


Expr compoundExpr(char P, const Expr& e1,const Expr& e2)
{

    /*
     * 合成两个表达式
     */

    Expr ans;
    ans.existVar = e1.existVar || e2.existVar;

    ans.root = new Node(P);
    ans.root->left = ans.clone(e1.root);
    ans.root->right = ans.clone(e2.root);
    ans.root->existVar = e1.existVar || e2.existVar;


    if(!ans.existVar)
    {
        ans.root->val = evaluate(P,e1.root->val,e2.root->val);
    }
    else
    {
        ans.root->val = 0;
    }
    ans.prefix = QString(P) + e1.prefix + e2.prefix;
    return ans;

}
