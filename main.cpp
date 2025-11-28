#include "expression.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Expression w;
    w.show();
    return a.exec();
}
