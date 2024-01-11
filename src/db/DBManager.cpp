//
// Created by Touka on 2024/1/7.
//

#include "DBManager.h"
#include <QSqlDatabase>
#include <QFile>
#include <QUuid>
#include <QSqlError>
#include <QSqlQuery>

#include "entity/Event.h"

namespace touka {

void DBManager::init() {
  const static QStringList CREATE_TABLE_SQLS = {
    R"(
CREATE TABLE IF NOT EXISTS events
(
    uid           TEXT PRIMARY KEY,
    summary       TEXT,
    description   TEXT,
    status        INTEGER,
    priority      INTEGER,
    all_day       BOOLEAN,
    private       BOOLEAN,
    dt_start      TEXT,
    dt_end        TEXT,
    created       TEXT,
    last_modified TEXT,
    tz            TEXT,
    location      TEXT,
    alarm_time    TEXT,
    cate_id       TEXT,
    FOREIGN KEY (cate_id) REFERENCES event_categories (cate_id)
);)",
    R"(
CREATE TABLE IF NOT EXISTS event_categories
(
    cate_id          TEXT PRIMARY KEY,
    cate_color       TEXT,
    cate_name        TEXT
);
)",
    R"(
CREATE TABLE IF NOT EXISTS recurrences
(
    event_uid TEXT PRIMARY KEY,
    freq      INTEGER,
    until     TEXT,
    count     INTEGER,
    interval  INTEGER,
    FOREIGN KEY (event_uid) REFERENCES events (uid)
);
)",
    R"(
CREATE TABLE IF NOT EXISTS byday
(
    recurrence_event_uid TEXT,
    day                  INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);
)",
    R"(
CREATE TABLE IF NOT EXISTS bymonthday
(
    recurrence_event_uid TEXT,
    day                  INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);)",
    R"(
CREATE TABLE IF NOT EXISTS byyearday
(
    recurrence_event_uid TEXT,
    day                  INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);
)",
    R"(
CREATE TABLE IF NOT EXISTS byweekno
(
    recurrence_event_uid TEXT,
    week                 INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);
)",
    R"(
CREATE TABLE IF NOT EXISTS bymonth
(
    recurrence_event_uid TEXT,
    month                INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);
)",
    R"(
CREATE TABLE IF NOT EXISTS bysetpos
(
    recurrence_event_uid TEXT,
    position             INTEGER,
    FOREIGN KEY (recurrence_event_uid) REFERENCES recurrences (event_uid)
);)"};

  db_ = std::make_unique<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
  db_->setDatabaseName(DB_DIR.data());
  db_->setConnectOptions("QSQLITE_BUSY_TIMEOUT=10000");
  const bool dbExists = QFile::exists(DB_DIR.data());

  if (!db_->open()) {
    qCritical() << "Cannot open database:" << db_->lastError().text();
    return;
  }

  QSqlQuery query(*db_);
  for (const auto &sql : CREATE_TABLE_SQLS) {
    if (!query.exec(sql)) {
      qCritical() << "Failed to create table:" << query.lastError().text();
    }
  }

  if (dbExists) return;
  QStringList queries;
  queries << "INSERT INTO event_categories VALUES('0', '#1E90FF', 'default');"
          << "INSERT INTO event_categories VALUES('1', '#C25656', 'birthday');";

  for (const auto& q : queries)
    if (!query.exec(q))
      qCritical() << "Failed to execute query:" << query.lastError().text();

}

DBManager::DBManager() {
  init();
  readCatefories();
  readEvents();
}

DBManager::~DBManager() { db_->close(); }

bool DBManager::addEvent(const EventPtr &event) {
  if (!event) return false;
  event->set_uid(generateUID());
  event->set_created(QDateTime::currentDateTime());
  event->set_last_modified(event->get_created());
  QSqlQuery query(*db_);
  query.prepare(
      "INSERT INTO events (uid, summary, description, status, priority, "
      "all_day, private, dt_start, dt_end, created, last_modified, "
      "tz, location, alarm_time, cate_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, "
      "?, ?, ?, ?, ?, ?)");
  query.addBindValue(event->get_uid());
  query.addBindValue(event->get_summary());
  query.addBindValue(event->get_description());
  query.addBindValue(EnumUtils::toUnderlying(event->get_status()));
  query.addBindValue(event->get_priority());
  query.addBindValue(event->is_all_day());
  query.addBindValue(event->is_private());
  query.addBindValue(event->get_dt_start().toString(Qt::ISODate));
  query.addBindValue(event->get_dt_end().toString(Qt::ISODate));
  query.addBindValue(event->get_created().toString(Qt::ISODate));
  query.addBindValue(event->get_last_modified().toString(Qt::ISODate));
  query.addBindValue(event->get_tz().id());
  query.addBindValue(event->get_location());
  const auto alarmTimeOptional = event->get_alarm_time();
  query.addBindValue(alarmTimeOptional ? alarmTimeOptional.value() : QVariant(QDateTime()));
  if (event->get_categories())
    query.addBindValue(event->get_categories()->get_cate_id());
  else
    query.addBindValue({});

  if (query.exec()) {
    event_cache_[event->get_uid()] = event;
    return true;
  }
  return false;
}

bool DBManager::updateEvent(const EventPtr &existingEvent,
                            const EventPtr &newEvent) {
  if (!existingEvent || !newEvent) return false;
  return updateEventById(existingEvent->get_uid().toStdString().c_str(), newEvent);
}

bool DBManager::updateEventById(const char *eventId, const EventPtr &newEvent) {
  if (!eventId || !newEvent) return false;
  QSqlQuery query(*db_);
  query.prepare(
      "UPDATE events SET summary = ?, description = ?, status = ?, priority = "
      "?, all_day = ?, private = ?, dt_start = ?, dt_end = ?, "
      "last_modified = ?, tz = ?, location = ?, alarm_time = ?, cate_id = ? "
      "WHERE uid = ?");
  query.addBindValue(newEvent->get_summary());
  query.addBindValue(newEvent->get_description());
  query.addBindValue(EnumUtils::toUnderlying(newEvent->get_status()));
  query.addBindValue(newEvent->get_priority());
  query.addBindValue(newEvent->is_all_day());
  query.addBindValue(newEvent->is_private());
  query.addBindValue(newEvent->get_dt_start().toString(Qt::ISODate));
  query.addBindValue(newEvent->get_dt_end().toString(Qt::ISODate));
  query.addBindValue(newEvent->get_last_modified().toString(Qt::ISODate));
  query.addBindValue(newEvent->get_tz().id());
  query.addBindValue(newEvent->get_location());
  const auto alarmTimeOptional = newEvent->get_alarm_time();
  const auto alarmTime = alarmTimeOptional ? alarmTimeOptional->toString(Qt::ISODate) : nullptr;
  query.addBindValue(alarmTime);
  if (newEvent->get_categories())
    query.addBindValue(newEvent->get_categories()->get_cate_id());
  else
    query.addBindValue({});
  query.addBindValue(eventId);

  if (query.exec()) {
    event_cache_[newEvent->get_uid()] = newEvent;
    return true;
  }
  return false;
}

std::shared_ptr<Event> DBManager::getEventById(const String &eventId) {
  const auto event = event_cache_.find(eventId);
  if (event != event_cache_.end())
    return event->second;

  auto eventPtr = std::make_shared<Event>();
  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM events WHERE uid = ?");
  query.addBindValue(eventId);
  if (!query.exec()) return nullptr;
  eventPtr->set_uid(query.value(0).toString());
  eventPtr->set_summary(query.value(1).toString());
  eventPtr->set_description(query.value(2).toString());
  eventPtr->set_status(static_cast<Status>(query.value(3).toInt()));
  eventPtr->set_priority(static_cast<Priority>(query.value(4).toInt()));
  eventPtr->set_all_day(query.value(5).toBool());
  eventPtr->set_private(query.value(6).toBool());
  eventPtr->set_dt_start(query.value(7).toDateTime());
  eventPtr->set_dt_end(query.value(8).toDateTime());
  eventPtr->set_created(query.value(9).toDateTime());
  eventPtr->set_last_modified(query.value(10).toDateTime());
  eventPtr->set_tz(query.value(11).toDateTime().timeZone());
  eventPtr->set_location(query.value(12).toString());
  eventPtr->set_alarm_time(query.value(13).toDateTime());
  eventPtr->set_categories(getCategoryByName(query.value(14).toString().toStdString().c_str()));

  event_cache_[eventPtr->get_uid()] = eventPtr;
  return eventPtr;
}

std::shared_ptr<Event>
DBManager::getEventByNameAndTime(const char *eventName,
                                 const DateTime &startTime) {}

EventPtr DBManager::createEventFromQuery(const QSqlQuery&query) {
  auto eventPtr = std::make_shared<Event>();
  eventPtr->set_uid(query.value(0).toString());
  eventPtr->set_summary(query.value(1).toString());
  eventPtr->set_description(query.value(2).toString());
  eventPtr->set_status(static_cast<Status>(query.value(3).toInt()));
  eventPtr->set_priority(static_cast<Priority>(query.value(4).toInt()));
  eventPtr->set_all_day(query.value(5).toBool());
  eventPtr->set_private(query.value(6).toBool());
  eventPtr->set_dt_start(query.value(7).toDateTime());
  eventPtr->set_dt_end(query.value(8).toDateTime());
  eventPtr->set_created(query.value(9).toDateTime());
  eventPtr->set_last_modified(query.value(10).toDateTime());
  eventPtr->set_tz(query.value(11).toDateTime().timeZone());
  eventPtr->set_location(query.value(12).toString());
  eventPtr->set_alarm_time(query.value(13).toDateTime());
  eventPtr->set_categories(getCategoryById(query.value(14).toString().toStdString().c_str()));
  return eventPtr;
}

EventPtrList DBManager::getEventsByName(const char* eventName) {
  EventPtrList events;
  if (!eventName) return events;
  for (const auto & [_, evt] : event_cache_) {
    if (evt->get_summary() == eventName)
      events.push_back(evt);
  }
  if (!events.empty()) return events;

  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM events WHERE summary = ?");
  query.addBindValue(eventName);
  if (query.exec()) {
    while (query.next()) {
      auto eventPtr = createEventFromQuery(query);
      event_cache_[eventPtr->get_uid()] = eventPtr;
      events.push_back(eventPtr);
    }
  }
  return events;
}

QVector<std::shared_ptr<Event>> DBManager::getEventsOfDay(const Date &date) {
  EventPtrList events;
  for (const auto & [_, evt] : event_cache_) {
    if (evt->get_dt_start().date() == date)
      events.push_back(evt);
  }
  if (!events.empty()) return events;

  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM events WHERE dt_start = ?");
  query.addBindValue(date.toString(Qt::ISODate));
  if (query.exec()) {
    while (query.next()) {
      auto eventPtr = createEventFromQuery(query);
      event_cache_[eventPtr->get_uid()] = eventPtr;
      events.push_back(eventPtr);
    }
  }
  return events;
}

QVector<std::shared_ptr<Event>> DBManager::getEventsOfWeek(const Date &date) {
  EventPtrList events;
  const auto weekNum = date.weekNumber();
  for (const auto & [_, evt] : event_cache_) {
    if (evt->get_dt_start().date().weekNumber() == weekNum)
      events.push_back(evt);
  }
  if (!events.empty()) return events;

  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM events WHERE strftime('%W', dt_start) = ?");
  query.addBindValue(weekNum);
  if (query.exec()) {
    while (query.next()) {
      auto eventPtr = createEventFromQuery(query);
      event_cache_[eventPtr->get_uid()] = eventPtr;
      events.push_back(eventPtr);
    }
  }
  return events;
}

QVector<std::shared_ptr<Event>> DBManager::getEventsOfMonth(const Date &date) {
  EventPtrList events;
  const auto monthNum = date.month();
  for (const auto & [_, evt] : event_cache_) {
    if (evt->get_dt_start().date().month() == monthNum)
      events.push_back(evt);
  }
  if (!events.empty()) return events;

  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM events WHERE strftime('%m', dt_start) = ?");
  query.addBindValue(monthNum);
  if (query.exec()) {
    while (query.next()) {
      auto eventPtr = createEventFromQuery(query);
      event_cache_[eventPtr->get_uid()] = eventPtr;
      events.push_back(eventPtr);
    }
  }
  return events;
}

QVector<std::shared_ptr<Event>>
DBManager::getEventsInInterval(const DateTime &start, const DateTime &end) {
  EventPtrList events;
  for (const auto & [_, evt] : event_cache_) {
    if (evt->get_dt_start() >= start && evt->get_dt_end() <= end)
      events.push_back(evt);
  }
  if (!events.empty()) return events;

  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM events WHERE dt_start >= ? AND dt_end <= ?");
  query.addBindValue(start.toString(Qt::ISODate));
  query.addBindValue(end.toString(Qt::ISODate));
  if (query.exec()) {
    while (query.next()) {
      auto eventPtr = createEventFromQuery(query);
      event_cache_[eventPtr->get_uid()] = eventPtr;
      events.push_back(eventPtr);
    }
  }
  return events;
}

QVector<std::shared_ptr<Event>>
DBManager::getEventsOfCategory(const EventCategories *category) {
  EventPtrList events;
  if (!category) return events;
  for (const auto & [_, evt] : event_cache_) {
    if (evt->get_categories()->get_cate_id() == category->get_cate_id())
      events.push_back(evt);
  }
  if (!events.empty()) return events;

  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM events WHERE cate_id = ?");
  query.addBindValue(category->get_cate_id());
  if (query.exec()) {
    while (query.next()) {
      auto eventPtr = createEventFromQuery(query);
      event_cache_[eventPtr->get_uid()] = eventPtr;
      events.push_back(eventPtr);
    }
  }
  return events;
}

bool DBManager::removeEvent(const EventPtr &event) {
  if (!event) return false;
  QSqlQuery query(*db_);
  query.prepare("DELETE FROM events WHERE uid = ?");
  query.addBindValue(event->get_uid());
  if (query.exec()) {
    event_cache_.erase(event->get_uid());
    return true;
  }
  return false;
}

bool DBManager::restoreEvent(const EventPtr &eventPtr) {
  if (!eventPtr) return false;
  const auto eventId = eventPtr->get_uid().toStdString().c_str();
  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM events WHERE uid = ?");
  query.addBindValue(eventId);
  if (!query.exec()) return false;
  eventPtr->set_uid(query.value(0).toString());
  eventPtr->set_summary(query.value(1).toString());
  eventPtr->set_description(query.value(2).toString());
  eventPtr->set_status(static_cast<Status>(query.value(3).toInt()));
  eventPtr->set_priority(static_cast<Priority>(query.value(4).toInt()));
  eventPtr->set_all_day(query.value(5).toBool());
  eventPtr->set_private(query.value(6).toBool());
  eventPtr->set_dt_start(query.value(7).toDateTime());
  eventPtr->set_dt_end(query.value(8).toDateTime());
  eventPtr->set_created(query.value(9).toDateTime());
  eventPtr->set_last_modified(query.value(10).toDateTime());
  eventPtr->set_tz(query.value(11).toDateTime().timeZone());
  eventPtr->set_location(query.value(12).toString());
  eventPtr->set_alarm_time(query.value(13).toDateTime());
  eventPtr->set_categories(getCategoryByName(query.value(14).toString().toStdString().c_str()));

  event_cache_[eventPtr->get_uid()] = eventPtr;
  return true;
}

bool DBManager::addCategory(const CategoryPtr &category) {
  if (!category) return false;
  QSqlQuery query(*db_);
  category->set_cate_id(generateUID());
  query.prepare("INSERT INTO event_categories (cate_id, cate_color, cate_name) "
                "VALUES (?, ?, ?)");
  query.addBindValue(category->get_cate_id());
  query.addBindValue(category->get_cate_color().name());
  query.addBindValue(category->get_cate_name());
  if (query.exec()) {
    category_cache_[category->get_cate_id()] = category;
    return true;
  }
  return false;
}

bool DBManager::updateCategory(const CategoryPtr &oldCategory,
                               const CategoryPtr &newCategory) {
  if (!oldCategory || !newCategory) return false;
  QSqlQuery query(*db_);
  query.prepare("UPDATE event_categories SET cate_name = ?, cate_color = ? "
                "WHERE cate_id = ?");
  query.addBindValue(newCategory->get_cate_name());
  query.addBindValue(newCategory->get_cate_color().name());
  query.addBindValue(oldCategory->get_cate_id());
  newCategory->set_cate_id(oldCategory->get_cate_id());
  if (query.exec()) {
    category_cache_[newCategory->get_cate_id()] = newCategory;
    return true;
  }
  return false;
}

CategoryPtr DBManager::getCategoryById(const String &categoryId) {
  const auto category = category_cache_.find(categoryId);
  if (category != category_cache_.end())
    return category->second;

  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM event_categories WHERE cate_id = ?");
  query.addBindValue(categoryId);
  if (query.exec() && query.next()) {
    auto evtCategory = std::make_shared<EventCategories>(
        query.value(0).toString(), query.value(1).toString(),
        query.value(2).toString());
    category_cache_[evtCategory->get_cate_id()] = evtCategory;
    return evtCategory;
  }
  return nullptr;
}

CategoryPtr DBManager::getCategoryByName(const String &categoryName) {
  for (const auto & [uid, category] : category_cache_) {
    if (category->get_cate_name() == categoryName)
      return category;
  }

  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM event_categories WHERE cate_name = ?");
  query.addBindValue(categoryName);
  if (query.exec() && query.next()) {
    auto category = std::make_shared<EventCategories>(
        query.value(0).toString(), query.value(1).toString(),
        query.value(2).toString());
    return category;
  }
  return nullptr;
}

void DBManager::readCatefories() {
  category_cache_.clear();
  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM event_categories");
  if (query.exec()) {
    while (query.next()) {
      const auto category = std::make_shared<EventCategories>(
        query.value(0).toString(), query.value(1).toString(),
        query.value(2).toString());
      category_cache_[category->get_cate_id()] = category;
    }
  }
}

void DBManager::readEvents() {
  event_cache_.clear();
  QSqlQuery query(*db_);
  query.prepare("SELECT * FROM events");
  if (query.exec()) {
    while (query.next()) {
      const auto eventPtr = createEventFromQuery(query);
      event_cache_[eventPtr->get_uid()] = eventPtr;
    }
  }
}

CategoryPtrList
DBManager::getAllCategories() {
  CategoryPtrList categories;
  if (category_cache_.empty())
    readCatefories();
  for (const auto & [uid, category] : category_cache_) {
    categories.push_back(category);
  }
  return categories;
}

bool DBManager::removeCategory(const CategoryPtr &category) {
  if (!category) return false;
  QSqlQuery query(*db_);
  query.prepare("DELETE FROM event_categories WHERE cate_id = ?");
  query.addBindValue(category->get_cate_id());
  if (query.exec()) {
    category_cache_.erase(category->get_cate_id());
    return true;
  }
  return false;
}

Id DBManager::generateUID() {
  return QUuid::createUuid().toString(QUuid::WithoutBraces);
}

bool DBManager::addRecurrence(const Recurrence &recurrence) {}

bool DBManager::updateRecurrence(const Recurrence &existingRecurrence,
                                 const Recurrence &newRecurrence) {}

bool DBManager::removeRecurrence(const Recurrence &recurrence) {}

std::shared_ptr<Recurrence>
DBManager::getRecurrenceByEventId(const std::string &eventId) {}

std::vector<int> DBManager::getRecurrenceByDay(const std::string &eventId) {}

std::vector<int>
DBManager::getRecurrenceByMonthDay(const std::string &eventId) {}

std::vector<int> DBManager::getRecurrenceByYearDay(const std::string &eventId) {
}

std::vector<int> DBManager::getRecurrenceByWeekNo(const std::string &eventId) {}

std::vector<int> DBManager::getRecurrenceByMonth(const std::string &eventId) {}

std::vector<int> DBManager::getRecurrenceBySetPos(const std::string &eventId) {}

bool DBManager::updateRecurrenceByDay(const std::string &eventId,
                                      const std::vector<int> &byDay) {}

bool DBManager::updateRecurrenceByMonthDay(const std::string &eventId,
                                           const std::vector<int> &byMonthDay) {
}

bool DBManager::updateRecurrenceByYearDay(const std::string &eventId,
                                          const std::vector<int> &byYearDay) {}

bool DBManager::updateRecurrenceByWeekNo(const std::string &eventId,
                                         const std::vector<int> &byWeekNo) {}

bool DBManager::updateRecurrenceByMonth(const std::string &eventId,
                                        const std::vector<int> &byMonth) {}

bool DBManager::updateRecurrenceBySetPos(const std::string &eventId,
                                         const std::vector<int> &bySetPos) {}
} // namespace touka