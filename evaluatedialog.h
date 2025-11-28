#ifndef EVALUATEDIALOG_H
#define EVALUATEDIALOG_H

#include <QDialog>
#include "ExprStruct.h"
namespace Ui {
class EvaluateDialog;
}

class EvaluateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EvaluateDialog(const Expr& e,QWidget *parent = nullptr);
    ~EvaluateDialog();

private slots:
    void on_calculateButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::EvaluateDialog *ui;

    Expr expression;

    void initTable();
};

#endif // EVALUATEDIALOG_H
