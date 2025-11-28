#include "expression.h"
#include "ui_expression.h"

#include "inputwidget.h"
#include "showwidget.h"
#include "evaluatewidget.h"
#include "compoundwidget.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Expression::Expression(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Expression)
{
    ui->setupUi(this);

    // connect(ui->actionOpen_O, &QAction::triggered, this, &Expression::on_actionOpen_O_triggered);
    // connect(ui->actionSave_S, &QAction::triggered, this, &Expression::on_actionSave_S_triggered);
}

void Expression::on_actionOpen_O_triggered()
{

    QString filePath = QFileDialog::getOpenFileName(this, tr("打开文件"),tr(""),tr("文本文件 (*.txt);;所有文件 (*)"));

    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("无法打开文件:\n%1").arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QString line;
    expressions.clear();
    while(!in.atEnd())
    {
        line = in.readLine();
        if (line.trimmed().isEmpty()) continue;
        expressions.push_back(createExpr(line));
    }
    file.close();
}



void Expression::on_actionSave_S_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("保存文件"),
                                                    "",
                                                    tr("文本文件 (*.txt);;所有文件 (*)"));



    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("无法保存文件:\n%1").arg(file.errorString()));
        return;
    }

    QTextStream out(&file);

    for(size_t i = 0; i < expressions.size(); ++i)
    {
        out << expressions[i].prefix << "\n";
    }

    file.close();
}

Expression::~Expression()
{
    delete ui;
}

void Expression::on_inputButton_clicked()
{
    InputWidget *input = new InputWidget;

    input->setAttribute(Qt::WA_DeleteOnClose);

    this->hide();
    input->show();

    connect(input,&InputWidget::returnExpr,this,&Expression::getExpressions);

    connect(input,&InputWidget::destroyed,[=]{
        this->show();
    });
}

void Expression::getExpressions(const std::vector<Expr>& vec)
{
    for(size_t i = 0; i < vec.size(); ++i)
    {
        expressions.push_back(vec[i]);
    }
}

void Expression::getExpression(const Expr& exp)
{
    expressions.push_back(exp);
}

void Expression::on_showButton_clicked()
{
    ShowWidget *show = new ShowWidget(expressions);

    show->setAttribute(Qt::WA_DeleteOnClose);

    this->hide();
    show->show();

    connect(show,&ShowWidget::destroyed,[=]{
        this->show();
    });
}


void Expression::on_evaluateButton_clicked()
{
    EvaluateWidget *evaluate = new EvaluateWidget(expressions);

    evaluate->setAttribute(Qt::WA_DeleteOnClose);

    this->hide();
    evaluate->show();

    connect(evaluate,&EvaluateWidget::destroyed,[=]{
        this->show();
    });
}


void Expression::on_compoundButton_clicked()
{
    CompoundWidget  *compound = new CompoundWidget(expressions);

    compound->setAttribute(Qt::WA_DeleteOnClose);

    this->hide();
    compound->show();

    connect(compound,&CompoundWidget::returnExpr,this,&Expression::getExpression);

    connect(compound,&CompoundWidget::destroyed,[=]{
        this->show();
    });
}

