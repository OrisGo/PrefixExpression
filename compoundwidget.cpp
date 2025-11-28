#include "compoundwidget.h"
#include "ui_compoundwidget.h"

#include <QMessageBox>

CompoundWidget::CompoundWidget(const std::vector<Expr>& expression,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CompoundWidget)
{
    ui->setupUi(this);


    for(size_t i = 0; i < expression.size(); ++i)
    {
        ui->OprandBox1->addItem(expression[i].prefix);
        ui->OprandBox2->addItem(expression[i].prefix);
    }
}

CompoundWidget::~CompoundWidget()
{
    delete ui;
}



void CompoundWidget::on_exitButton_clicked()
{
    this->close();
}


void CompoundWidget::on_readButton_clicked()
{
    QString s = ui->opComboBox->currentText() + ui->OprandBox1->currentText() + ui->OprandBox2->currentText();
    if(validPrefix(s))
    {
        emit returnExpr(createExpr(s));
        QMessageBox::information(this,"提示","表达式输入成功");
    }
    else
    {
        QMessageBox::warning(this,"警告","无效的前缀的表达式");
    }
}

