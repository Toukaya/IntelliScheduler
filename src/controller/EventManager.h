//
// Created by Touka on 2023/12/15.
//

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <async_simple/coro/Lazy.h>
#include <QtCore/QObject>

#include "types.hpp"


namespace touka {
    class EventCategories;
}

namespace touka {

    class Event;

class EventManager : public QObject{
    // Q_OBJECT

public:
    static std::vector<Event> parseICalFormat(std::istringstream& icalDataStream);
    static String toICalFormat(const Event &evt);
    static Event iCalFormatToEvt(const String &icalDataStream);
    static String exportICalFormat(const std::vector<Event> &evts);

    void addEvent(const Event &evt);
    void deleteEvent(const Event &evt);
    std::vector<Event> getEventsOnDate(const QDate &date);
    std::vector<Event> getEventsInRange(const QDate &start, const QDate &end);
    std::vector<Event> searchEvents(const String &query);
    void modifyEvent(const Event &oldEvent, const Event &newEvent);

    auto getEventSync(const String&uid) -> async_simple::coro::Lazy<Event>;
    auto getEventsOnDateSync(const QDate&date) -> async_simple::coro::Lazy<std::vector<Event>>;
    auto getEventsInRangeSync(const QDate&start, const QDate&end) -> async_simple::coro::Lazy<std::vector<Event>>;
    auto searchEventsSync(const String&query) -> async_simple::coro::Lazy<std::vector<Event>>;
    auto addEventSync(const Event&evt) -> async_simple::coro::Lazy<>;
    auto deleteEventSync(const Event&evt) -> async_simple::coro::Lazy<>;
    auto modifyEventSync(const Event&oldEvent, const Event&newEvent) -> async_simple::coro::Lazy<>;

    static std::vector<EventCategories> getEvtCategories();
    
signals:
    void eventAdded(const Event &evt);
    void eventDeleted(const Event &evt);
    void eventModified(const Event &oldEvent, const Event &newEvent);

    public slots:
    void onEventAdded(const Event &evt);
    void onEventRemoved(const Event &evt);
    void onEventUpdated(const Event &evt);

private:

    // const auto eventCompare = [](const Event& a, const Event& b) {
    //     return a.get_dt_start() < b.get_dt_start();
    // };

    // std::map<Date, std::vector<Event>, decltype(eventCompare)> events_{eventCompare};

};

} // touka

#endif //EVENTMANAGER_H
