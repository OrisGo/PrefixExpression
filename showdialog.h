#ifndef SHOWDIALOG_H
#define SHOWDIALOG_H

#include <QDialog>
#include "ExprStruct.h"
namespace Ui {
class ShowDialog;
}

class ShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowDialog(Expr& e,QWidget *parent = nullptr);
    ~ShowDialog();

private:
    Ui::ShowDialog *ui;
};

#endif // SHOWDIALOG_H
