#ifndef CALCULATEWIDGET_H
#define CALCULATEWIDGET_H

#include <QWidget>
#include "ExprStruct.h"
namespace Ui {
class EvaluateWidget;
}

class CalculateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalculateWidget(std::vector<Expr>& vec,QWidget *parent = nullptr);
    ~CalculateWidget();

private:
    Ui::EvaluateWidget *ui;

    std::vector<Expr> expressions;
};

#endif // CALCULATEWIDGET_H
