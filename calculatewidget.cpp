#include "calculatewidget.h"
#include "ui_calculatewidget.h"

#include "calculatedialog.h"
CalculateWidget::CalculateWidget(std::vector<Expr>& vec,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EvaluateWidget)
{
    ui->setupUi(this);

    for(size_t i = 0; i < vec.size(); ++i)
    {
        ui->listWidget->addItem(vec[i].prefix);
    }

    expressions = vec;

    connect(ui->listWidget, &QListWidget::itemDoubleClicked,
            this, [=](QListWidgetItem *item){
                int row = ui->listWidget->row(item);

                if(row >= 0 && row < static_cast<int>(expressions.size())) {

                    Expr& targetExpr = expressions[row];

                    CalculateDialog *dlg = new CalculateDialog(targetExpr, this);

                    dlg->setAttribute(Qt::WA_DeleteOnClose);

                    dlg->exec();
                }
            });
}

CalculateWidget::~CalculateWidget()
{
    delete ui;
}
