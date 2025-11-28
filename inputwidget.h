#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include "ExprStruct.h"

namespace Ui {
class InputWidget;
}

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    std::vector<Expr> expressions;


    explicit InputWidget(QWidget *parent = nullptr);
    ~InputWidget();

private slots:
    void on_clearButton_clicked();

    void on_readButton_clicked();

    void on_exitButton_clicked();

signals:
    void returnExpr(const std::vector<Expr>& data) const;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::InputWidget *ui;
};

#endif // INPUTWIDGET_H
