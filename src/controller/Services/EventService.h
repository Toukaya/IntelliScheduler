//
// Created by Touka on 2024/1/7.
//

#ifndef EVENTSERVICE_H
#define EVENTSERVICE_H
#include "types.hpp"
#include "entity/Event.h"
class QDate;

namespace touka {
  class DBManager;

  class EventService {
  public:
    bool addEvent(const EventPtr&evt, DBManager&db);

    bool deleteEvent(const EventPtr&evt, DBManager&db);

    EventPtr getEventById(const String &eventId, DBManager&db);

    EventPtrList getEventsOnDate(const QDate&date, DBManager&db);

    EventPtrList getEventsOfWeek(const QDate&date, DBManager&db);

    EventPtrList getEventsOfMonth(const QDate&date, DBManager&db);

    EventPtrList getEventsOfCategory(const EventCategories*category, DBManager&db);

    EventPtrList getEventsInRange(const DateTime&start, const DateTime&end, DBManager&db);

    EventPtrList searchEventsByName(const String&query, DBManager&db);

    bool modifyEvent(const EventPtr&oldEvent, const EventPtr&newEvent, DBManager&db);
  };
} // touka

#endif //EVENTSERVICE_H
