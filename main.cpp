#include "AppConfig.hpp"
#include "entity/Event.h"
#include "view/mainwindow.h"
#include <QApplication>

Q_DECLARE_METATYPE(touka::EventPtr)

int main(int argc, char* argv[])
{
    qRegisterMetaType<std::shared_ptr<touka::Event>>("std::shared_ptr<touka::Event>");
    qRegisterMetaType<touka::EventPtr>("EventPtr");
    QApplication a(argc, argv);
    touka::MainWindow m;
    m.show();
    return QApplication::exec();
}
