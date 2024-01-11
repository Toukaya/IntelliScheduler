//
// Created by Touka on 2024/1/7.
//

#include "EventService.h"
#include "db/DBManager.h"
#include <QDateTime>
namespace touka {
bool EventService::addEvent(const EventPtr& evt, DBManager& db) {
    if (!evt) return false;
    return db.addEvent(evt);
}

bool EventService::deleteEvent(const EventPtr& evt, DBManager& db) {
  if (!evt) return false;
  return db.removeEvent(evt);
}

EventPtr EventService::getEventById(const String &eventId, DBManager& db) {
  return db.getEventById(eventId.toStdString().c_str());
}

EventPtrList EventService::getEventsOnDate(const QDate& date, DBManager& db) {
  return db.getEventsOfDay(date);
}

EventPtrList EventService::getEventsOfWeek(const QDate& date, DBManager& db) {
  return db.getEventsOfWeek(date);
}

EventPtrList EventService::getEventsOfMonth(const QDate& date, DBManager& db) {
  return db.getEventsOfMonth(date);
}

EventPtrList EventService::getEventsOfCategory(const EventCategories* category, DBManager& db) {
  return db.getEventsOfCategory(category);
}

EventPtrList EventService::getEventsInRange(const DateTime& start, const DateTime& end, DBManager& db) {
  return db.getEventsInInterval(start, end);
}

EventPtrList EventService::searchEventsByName(const String& query, DBManager& db) {
  return db.getEventsByName(query.toStdString().c_str());
}

bool EventService::modifyEvent(const EventPtr& oldEvent, const EventPtr& newEvent, DBManager& db) {
  if (!oldEvent || !newEvent) return false;
  return db.updateEvent(oldEvent, newEvent);
}
} // touka