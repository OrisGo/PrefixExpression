#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QMainWindow>
#include "ExprStruct.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class Expression;
}
QT_END_NAMESPACE

class Expression : public QMainWindow
{
    Q_OBJECT

public:
    Expression(QWidget *parent = nullptr);
    ~Expression();

private slots:
    void on_inputButton_clicked();

    void getExpressions(const std::vector<Expr>& vec);
    void getExpression(const Expr& exp);

    void on_showButton_clicked();

    void on_evaluateButton_clicked();

    void on_compoundButton_clicked();

    void on_actionOpen_O_triggered(); // 声明 Open 动作的槽函数
    void on_actionSave_S_triggered(); // 声明 Save 动作的槽函数

signals:
    void sendExpressions(const std::vector<Expr>& vec);


private:
    Ui::Expression *ui;

    std::vector<Expr> expressions;
};
#endif // EXPRESSION_H
