//
// Created by Touka on 2023/12/19.
//

#ifndef EVENTREPOSITORY_H
#define EVENTREPOSITORY_H
#include <unordered_map>
#include <async_simple/coro/FutureAwaiter.h>
#include <async_simple/coro/Lazy.h>
#include <QtCore/QObject>

class QString;
class QSqlDatabase;
class QSqlTableModel;

namespace touka {
    class EventCategories;
    class Event;

    class EventRepository : public QObject {
    public:
        static EventRepository& getInstance();

        async_simple::Future<void> connectDBSync();
        async_simple::Future<void> addEvtSync(const Event&evt);
        async_simple::Future<void> deleteEvtSync(const Event&evt);
        async_simple::Future<void> modifyEvtSync(const Event&oldEvt, const Event&newEvt);
        async_simple::Future<std::vector<Event>> getEventsOnDateSync(const QDate&date);

        std::vector<EventCategories> getCategories();

    signals:
        void eventAdded(const Event&evt);

        void eventDeleted(const Event&evt);

        void eventModified(const Event&oldEvent, const Event&newEvent);

        void DBconnected();

        void DBdisconnected();

    public slots:
        void connectDB() const;

        void disconnectDB() const;

        void addEvt(const Event&evt);

        void deleteEvt(const Event&evt);

        void modifyEvt(const Event&oldEvt, const Event&newEvt);

        std::vector<Event> getEventsOnDate(const QDate&date);

    private:
        EventRepository();

        std::shared_ptr<QSqlDatabase> database_;

        std::unordered_map<QString, std::shared_ptr<QSqlTableModel>> tableModels_;

    public:
        EventRepository(const EventRepository&) = delete;

        EventRepository(EventRepository&&) = delete;

        EventRepository& operator=(const EventRepository&) = delete;

        EventRepository& operator=(EventRepository&&other) = delete;
    };
} // touka

#endif //EVENTREPOSITORY_H
