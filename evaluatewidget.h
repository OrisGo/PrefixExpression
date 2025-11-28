#ifndef EVALUATEWIDGET_H
#define EVALUATEWIDGET_H

#include <QWidget>
#include "ExprStruct.h"
namespace Ui {
class EvaluateWidget;
}

class EvaluateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EvaluateWidget(std::vector<Expr>& vec,QWidget *parent = nullptr);
    ~EvaluateWidget();

private:
    Ui::EvaluateWidget *ui;

    std::vector<Expr> expressions;
};

#endif // EVALUATEWIDGET_H
