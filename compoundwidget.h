#ifndef COMPOUNDWIDGET_H
#define COMPOUNDWIDGET_H

#include <QWidget>
#include "ExprStruct.h"
namespace Ui {
class CompoundWidget;
}

class CompoundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CompoundWidget(const std::vector<Expr>& vec,QWidget *parent = nullptr);
    ~CompoundWidget();

signals:
    void returnExpr(const Expr& data) const;

private slots:
    void on_exitButton_clicked();

    void on_readButton_clicked();

private:
    Ui::CompoundWidget *ui;
};

#endif // COMPOUNDWIDGET_H
