#include <QApplication>
#include "view/monthview.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    touka::MonthView m;
    m.show();
    return QApplication::exec();
}
