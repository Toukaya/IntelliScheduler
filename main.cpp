#include "AppConfig.hpp"
#include "entity/Event.h"
#include "view/mainwindow.h"
#include <QApplication>

#include "controller/AppManager.h"

Q_DECLARE_METATYPE(touka::EventPtr)

int main(int argc, char* argv[])
{
    qRegisterMetaType<std::shared_ptr<touka::Event>>("std::shared_ptr<touka::Event>");
    qRegisterMetaType<touka::EventPtr>("EventPtr");
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icon/resource/icon.svg"));
    touka::MainWindow m;
    QObject::connect(&touka::AppManager::instance(),&touka::AppManager::reminderTriggered,
                     &m, &touka::MainWindow::showTrayIconMessage);
    m.show();
    return QApplication::exec();
}
