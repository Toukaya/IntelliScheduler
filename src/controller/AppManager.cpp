//
// Created by Touka on 2023/12/15.
//

#include "AppManager.h"
#include "entity/Event.h"
#include <QSignalMapper>
#include <sstream>
#include <unordered_map>

namespace touka {
DBManager AppManager::db_manager_;
// void EventManager::subscribe(const String &eventId, const QObject *receiver,
//                              const char *method) {
//   // if (!signals_.contains(eventId)) {
//   //   signals_.insert(eventId, new QSignalMapper(this));
//   //   connect(signals_[eventId], SIGNAL(mapped()), receiver, method);
//   // }
//   // signals_[eventId]->setMapping(this, eventId);
// }

// std::vector<Event>
// EventManager::parseICalFormat(std::istringstream &icalDataStream) {
//   // TODO implement it
//   // 获取数据行
//   // 以行为单位进行解析
//   // 获取METHOD,若非PUBLISH
//   // 获取时区
//   return {};
// }
//
// String EventManager::toICalFormat(const Event &evt) {
//   std::ostringstream ss;
//   // ss << "BEGIN:VEVENT\n";
//   // ss << "UID:" << evt.get_uid().toStdString() << "\n";
//   // ss << "SUMMARY:" << evt.get_summary().toStdString() << "\n";
//   // ss << "DESCRIPTION:" << evt.get_description().toStdString() << "\n";
//   // ss << "CLASS:"
//   //    << EventUtils::classificationToString(evt.get_classification())
//   //           .toStdString()
//   //    << "\n";
//   // ss << "STATUS:" << EventUtils::statusToString(evt.get_status()).toStdString()
//   //    << "\n";
//   // // ss << "TRANSP:" <<
//   // // EventUtils::transparencyToString(evt.get_transp()).toStdString() << "\n";
//   // ss << "PRIORITY:"
//   //    << EventUtils::priorityToString(evt.get_priority()).toStdString() << "\n";
//   // ss << "DTSTART:" << evt.get_dt_start().toString().toStdString() << "\n";
//   // ss << "DTEND:" << evt.get_dt_end().toString().toStdString() << "\n";
//   // ss << "DTSTAMP:" << evt.get_dt_stamp().toString().toStdString() << "\n";
//   // ss << "CREATED:" << evt.get_created().toString().toStdString() << "\n";
//   // ss << "LAST-MODIFIED:"
//   //    << evt.get_last_modified().toString("yyyyMMddThhmmssZ").toStdString()
//   //    << "\n";
//   // ss << "LOCATION:" << evt.get_location().toStdString() << "\n";
//   // ss << "TZID:" << QString::fromUtf8(evt.get_tz().id()).toStdString() << "\n";
//   // ss << "RRULE:" << evt.get_rrule() << "\n";
//   // ss << "RECURRENCE-NO:" << evt.get_recurrence_no() << "\n";
//   // // ss << "RDATE:" << evt.get_rdate().toString().toStdString() << "\n";
//   // ss << "END:VEVENT\n";
//   return ss.str().data();
// }
//
// Event EventManager::iCalFormatToEvt(const String &icalDataStream) {}
//
// String EventManager::exportICalFormat(const std::vector<Event> &evts) {}
//
// void EventManager::addEvent(const Event &evt) {}
//
// void EventManager::deleteEvent(const Event &evt) {}
//
// std::vector<Event> EventManager::getEventsOnDate(const QDate &date) {}
//
// std::vector<Event> EventManager::getEventsInRange(const QDate &start,
//                                                   const QDate &end) {}
//
// std::vector<Event> EventManager::searchEvents(const String &query) {}
//
// void EventManager::modifyEvent(const Event &oldEvent, const Event &newEvent) {}

  AppManager::AppManager(QObject* parent) : QObject(parent) {
    const auto updateTodayEvt = [this] {
      const auto today = QDate::currentDate();
      const auto events = getEventsOfDay(today);
      reminderService_.updateTodayEvents(events);
    };
    connect(this, &AppManager::eventAdded, &reminderService_, &EventReminderService::addEvent);
    connect(this, &AppManager::eventDeleted, &reminderService_, updateTodayEvt);
    connect(this, &AppManager::eventModified, &reminderService_, updateTodayEvt);
    updateTodayEvt();
  }

  AppManager& AppManager::instance() {
    static AppManager instance;
    return instance;
  }

CategoryPtrList AppManager::getEvtCategories() {
  return db_manager_.getAllCategories();
}

CategoryPtr AppManager::getEvtCategoryById(const char* categoryId) {
    return db_manager_.getCategoryById(categoryId);
}

CategoryPtr AppManager::getEvtCategoryByName(const String &categoryName) {
    return db_manager_.getCategoryByName(categoryName);
}

EventPtr AppManager::createEmptyEvt(const std::optional<DateTime>&startTime) {
    auto evt = std::make_shared<Event>();
    auto dt = QDateTime::currentDateTime();
    if (startTime)
      dt = startTime.value();
    evt->set_dt_start(dt);
    evt->set_dt_end(dt);
    const auto cate = db_manager_.getCategoryById("0");
    evt->set_categories(cate);
    db_manager_.addEvent(evt);
    return evt;
}

void AppManager::addEvent(const EventPtr& evt) {
  const auto success = eventService_.addEvent(evt, db_manager_);
  if (success)
    emit eventAdded(evt);
}

void AppManager::deleteEvent(const EventPtr& evt) {
  const auto success = eventService_.deleteEvent(evt, db_manager_);
  if (success)
    emit eventDeleted(evt);
}

void AppManager::deleteEvent(const char* uid) {
  const auto evt = getEventById(uid);
  deleteEvent(evt);
}

void AppManager::modifyEvent(const EventPtr& oldEvent, const EventPtr& newEvent) {
  const auto success = eventService_.modifyEvent(oldEvent, newEvent, db_manager_);
  if (success)
    emit eventModified(oldEvent, newEvent);
}

EventPtr AppManager::getEventById(const String &eventId) {
  return eventService_.getEventById(eventId, db_manager_);
}

EventPtrList AppManager::getEventsOfDay(const Date& date) {
  return eventService_.getEventsOnDate(date, db_manager_);
}

EventPtrList AppManager::getEventsOfWeek(const Date& date) {
  return eventService_.getEventsOfWeek(date, db_manager_);
}

EventPtrList AppManager::getEventsOfMonth(const Date& date) {
  return eventService_.getEventsOfMonth(date, db_manager_);
}

EventPtrList AppManager::getEventsInInterval(const DateTime& start, const DateTime& end) {
  return eventService_.getEventsInRange(start, end, db_manager_);
}

EventPtrList AppManager::getEventsOfCategory(const EventCategories* category) {
  return eventService_.getEventsOfCategory(category, db_manager_);
}

EventPtrList AppManager::getEventsByName(const char* eventName) {
  return eventService_.searchEventsByName(eventName, db_manager_);
}

EventPtr AppManager::getEventByNameAndTime(const char* eventName, const DateTime& startTime) {
  // TODO implement it
  qCritical() << "Not implemented yet";
  return nullptr;
}

// void EventManager::onEventUpdated(const Event &evt) {
//   if (signals_.contains(evt.get_uid())) {
//     signals_[evt.get_uid()]->map();
//   }
// }
} // namespace touka