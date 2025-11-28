#ifndef CALCULATEDIALOG_H
#define CALCULATEDIALOG_H

#include <QDialog>
#include "ExprStruct.h"
namespace Ui {
class EvaluateDialog;
}

class CalculateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalculateDialog(const Expr& e,QWidget *parent = nullptr);
    ~CalculateDialog();

private slots:
    void on_calculateButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::EvaluateDialog *ui;

    Expr expression;

    void initTable();
};

#endif // CALCULATEDIALOG_H
