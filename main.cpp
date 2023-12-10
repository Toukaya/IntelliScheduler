#include <QApplication>

#include "view/mainwindow.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    touka::MainWindow m;
    m.show();
    return QApplication::exec();
}
