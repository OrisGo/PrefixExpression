#include "inputwidget.h"
#include "ui_inputwidget.h"
#include <QMessageBox>
#include "ExprStruct.h"

InputWidget::InputWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InputWidget)
{
    ui->setupUi(this);
}

InputWidget::~InputWidget()
{
    delete ui;
}

void InputWidget::on_clearButton_clicked()
{
    ui->lineEdit->clear();
}



void InputWidget::on_readButton_clicked()
{
    QString s = ui->lineEdit->text();
    if(validPrefix(s))
    {
        expressions.push_back(createExpr(s));
        QMessageBox::information(this,"提示","表达式输入成功");
    }
    else
    {
        QMessageBox::warning(this,"警告","无效的前缀的表达式");
    }
}


void InputWidget::on_exitButton_clicked()
{
    this->close();
}


void InputWidget::closeEvent(QCloseEvent* event)
{
    emit returnExpr(expressions);

    event->accept();
}
