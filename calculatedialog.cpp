#include "calculatedialog.h"
#include "ui_evaluatedialog.h"
#include <QMessageBox>


CalculateDialog::CalculateDialog(const Expr& e,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EvaluateDialog)
{
    ui->setupUi(this);
    expression = e;

    ui->lineEdit->setText(e.toInfix());

    initTable();
}

CalculateDialog::~CalculateDialog()
{
    delete ui;
}

void CalculateDialog::initTable()
{
    ui->tableWidget->setRowCount(0);

    for(auto it = expression.varMap.begin(); it != expression.varMap.end(); it++)
    {
        char varName = it->first;
        int varValue = (it->second = 0);

        int row = ui->tableWidget->rowCount();

        ui->tableWidget->insertRow(row);


        QTableWidgetItem *keyItem = new QTableWidgetItem(QString(QChar(varName)));

        keyItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        ui->tableWidget->setItem(row, 0, keyItem);

        QTableWidgetItem *valItem = new QTableWidgetItem(QString::number(varValue));
        valItem->setBackground(QColor(Qt::transparent));

        ui->tableWidget->setItem(row, 1 , valItem);
    }
}

void CalculateDialog::on_calculateButton_clicked()
{
    int rows = ui->tableWidget->rowCount();
    bool allOk = true;

    for (int i = 0; i < rows; ++i) {
        QString keyStr = ui->tableWidget->item(i, 0)->text();
        if (keyStr.isEmpty()) continue;
        char key = keyStr.at(0).toLatin1();

        QString valStr = ui->tableWidget->item(i, 1)->text();

        bool ok;
        int value = valStr.toInt(&ok);

        if (ok) {
            expression.setVarValue(key, value);
            ui->tableWidget->item(i, 1)->setBackground(Qt::transparent);
        } else {
            allOk = false;
            ui->tableWidget->item(i, 1)->setBackground(QColor(255, 200, 200));
        }
    }

    if (!allOk) {
        QMessageBox::warning(this, "输入错误", "表格中包含非法的数字格式，请检查！");
        return;
    }
    double result = expression.value();

    ui->lineEdit->clear();
    ui->label->clear();
    ui->label->setText("求值：");
    ui->lineEdit->setText(QString::number(result));
}


void CalculateDialog::on_resetButton_clicked()
{
    ui->label->clear();
    ui->label->setText("前缀表达式：");

    ui->lineEdit->clear();
    ui->lineEdit->setText(expression.toInfix());

    int rows = ui->tableWidget->rowCount();
    for(int i = 0; i < rows; ++i)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 1);
        if(item) {
            item->setText("0");
            item->setBackground(QColor(Qt::transparent));
        }
    }
}

