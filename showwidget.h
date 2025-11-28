#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include "ExprStruct.h"


namespace Ui {
class ShowWidget;
}

class ShowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShowWidget(const std::vector<Expr>& v,QWidget *parent = nullptr);
    ~ShowWidget();

private:
    Ui::ShowWidget *ui;

    std::vector<Expr> expressions;
};

#endif // SHOWWIDGET_H
