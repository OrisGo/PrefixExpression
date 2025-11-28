#include "showwidget.h"
#include "ui_showwidget.h"
#include "showdialog.h"
ShowWidget::ShowWidget(const std::vector<Expr>& v,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShowWidget)
{

    ui->setupUi(this);

    for(size_t i = 0; i < v.size(); ++i)
    {
        ui->listWidget->addItem(v[i].prefix);
    }

    expressions = v;

    connect(ui->listWidget, &QListWidget::itemDoubleClicked,
            this, [=](QListWidgetItem *item){
                int row = ui->listWidget->row(item);

                if(row >= 0 && row < static_cast<int>(expressions.size())) {

                    Expr& targetExpr = expressions[row];

                    ShowDialog *dlg = new ShowDialog(targetExpr, this);

                    dlg->setAttribute(Qt::WA_DeleteOnClose);

                    dlg->exec();
                }
            });
}

ShowWidget::~ShowWidget()
{
    delete ui;
}
