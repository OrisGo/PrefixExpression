#include "showdialog.h"
#include "ui_showdialog.h"


ShowDialog::ShowDialog(Expr& e,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowDialog)
{
    ui->setupUi(this);

    ui->prefixLine->setText(e.prefix);

    ui->infixText->setText(e.toInfix());

    ui->treeText->setText(e.toTree());
}

ShowDialog::~ShowDialog()
{
    delete ui;
}
