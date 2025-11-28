#pragma once

#ifndef EXPRSTRUCT_H
#define EXPRSTRUCT_H



#include <qstring.h>
#include <cmath>
#include <unordered_map>
#include <QDebug>

inline bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}


double evaluate(char P, double val1, double val2);

struct Node
{
    /*
     * 二叉树结点
     * 若为叶子结点，操作树为 0~9 或 变量
     */

    double val = 0;

    bool isOperand;
    bool existVar;
    char c;
    Node* left = nullptr;
    Node* right = nullptr;


    Node(char P, bool isOperator = true);

    Node(const Node& other) = delete;

    // ~Node();
    // {
    //     // delete left;
    //     // delete right;
    // }
};



inline void destroy(Node* root)
{
    if(!root) return;

    destroy(root->left);
    destroy(root->right);

    delete root;
}



class Expr{
public:
    bool existVar = false;
    Node* root = nullptr;
    QString prefix;
    std::unordered_map<char,int> varMap;
public:
    Expr() = default;

    Expr(const Expr& other);

    Expr& operator=(const Expr& other);


    ~Expr();

    QString toInfix() const;

    void setVarValue(char c,int v);

    double value();

private:
    QString toInfix(Node* root) const;


    double evaluate(Node* root);

public:
    Node* clone(const Node* other);

};



bool validPrefix(QString s);



Expr createExpr(QString prefix);



Expr compoundExpr(char P, const Expr& e1,const Expr& e2);



#endif // EXPRSTRUCT_H
