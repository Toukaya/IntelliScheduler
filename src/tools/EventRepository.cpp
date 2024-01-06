//
// Created by Touka on 2023/12/19.
//

#include "EventRepository.h"

#include <QtCore/qsettings.h>
// #include <QtSql>
// #include <QSqlDatabase>

#include "types.hpp"
#include "entity/EventCategories.h"

namespace touka {

    EventRepository::EventRepository() : QObject(qApp)/*, database_(std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE")))*/ {
    }

    EventRepository& EventRepository::getInstance() {
        static EventRepository instance;
        return instance;
    }

    async_simple::Future<void> EventRepository::connectDBSync() {
        connectDB();
    }

    async_simple::Future<void> EventRepository::addEvtSync(const Event& evt) {
    }

    async_simple::Future<void> EventRepository::deleteEvtSync(const Event& evt) {
    }

    async_simple::Future<void> EventRepository::modifyEvtSync(const Event& oldEvt, const Event& newEvt) {
    }

    async_simple::Future<std::vector<Event>> EventRepository::getEventsOnDateSync(const QDate& date) {
    }

    std::vector<EventCategories> EventRepository::getCategories() {
        // TODO implement it
        EventCategories categories1(Qt::green, "test1", "test");
        EventCategories categories2(Qt::black, "test2", "test");
        EventCategories categories3(Qt::blue, "test3", "test");
        EventCategories categories4(Qt::red, "test4", "test");
        return {categories1, categories2, categories3, categories4};
    }

    void EventRepository::connectDB() const {
        const QSettings settings("config.ini", QSettings::IniFormat);
        const QString filePath = settings.value("database/file").toString();

        // database_->setDatabaseName(filePath);
        // database_->setConnectOptions("QSQLITE_BUSY_TIMEOUT=10000");
        //
        // if (!database_->open())
        //     qDebug() << "Failed to open the database:" << filePath << Qt::endl;
    }

    void EventRepository::disconnectDB() const {
        // database_->close();
    }

    void EventRepository::addEvt(const Event& evt) {

    }

    void EventRepository::deleteEvt(const Event& evt) {
    }

    void EventRepository::modifyEvt(const Event& oldEvt, const Event& newEvt) {
    }

    std::vector<Event> EventRepository::getEventsOnDate(const QDate& date) {
    }

} // touka