//
// Created by Touka on 2024/1/7.
//

#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <memory>
#include <qsqlquery.h>

#include "types.hpp"
#include "entity/Event.h"

class QSqlDatabase;

namespace touka {
class Recurrence;

constexpr static std::string_view DB_DIR = "./storage.db";

class DBManager {
public:
  DBManager();
  ~DBManager();

  bool addEvent(const EventPtr &event);
  bool updateEvent(const EventPtr &existingEvent, const EventPtr &newEvent);
  bool updateEventById(const char *eventId, const EventPtr &newEvent);

  EventPtr getEventById(const String &eventId);
  EventPtr getEventByNameAndTime(const char *eventName,
                                               const DateTime &startTime);

  EventPtrList getEventsByName(const char *eventName);
  EventPtrList getEventsOfDay(const Date &date);
  EventPtrList getEventsOfWeek(const Date &date);
  EventPtrList getEventsOfMonth(const Date &date);
  EventPtrList getEventsInInterval(const DateTime &start, const DateTime &end);
  EventPtrList getEventsOfCategory(const EventCategories *category);

  bool removeEvent(const EventPtr &event);
  bool restoreEvent(const EventPtr &eventPtr);

  bool addCategory(const CategoryPtr &category);
  bool updateCategory(const CategoryPtr &oldCategory,
                      const CategoryPtr &newCategory);
  CategoryPtr getCategoryById(const String &categoryId);
  CategoryPtr getCategoryByName(const String &categoryName);

  [[nodiscard]]
  CategoryPtrList getAllCategories();
  bool removeCategory(const CategoryPtr &category);

  static Id generateUID();

private:
  void init();

  // Recurrence related methods
  bool addRecurrence(const Recurrence &recurrence);
  bool updateRecurrence(const Recurrence &existingRecurrence,
                        const Recurrence &newRecurrence);
  bool removeRecurrence(const Recurrence &recurrence);
  std::shared_ptr<Recurrence>
  getRecurrenceByEventId(const std::string &eventId);

  // Methods for recurrence properties
  std::vector<int> getRecurrenceByDay(const std::string &eventId);
  std::vector<int> getRecurrenceByMonthDay(const std::string &eventId);
  std::vector<int> getRecurrenceByYearDay(const std::string &eventId);
  std::vector<int> getRecurrenceByWeekNo(const std::string &eventId);
  std::vector<int> getRecurrenceByMonth(const std::string &eventId);
  std::vector<int> getRecurrenceBySetPos(const std::string &eventId);

  // Methods to update recurrence properties
  bool updateRecurrenceByDay(const std::string &eventId,
                             const std::vector<int> &byDay);
  bool updateRecurrenceByMonthDay(const std::string &eventId,
                                  const std::vector<int> &byMonthDay);
  bool updateRecurrenceByYearDay(const std::string &eventId,
                                 const std::vector<int> &byYearDay);
  bool updateRecurrenceByWeekNo(const std::string &eventId,
                                const std::vector<int> &byWeekNo);
  bool updateRecurrenceByMonth(const std::string &eventId,
                               const std::vector<int> &byMonth);
  bool updateRecurrenceBySetPos(const std::string &eventId,
                                const std::vector<int> &bySetPos);

  EventPtr createEventFromQuery(const QSqlQuery&query);

  void readCatefories();

  void readEvents();

  std::unordered_map<String, EventPtr> event_cache_;
  std::unordered_map<String, CategoryPtr> category_cache_;
  std::unordered_map<String, std::shared_ptr<Recurrence>> rrule_cache_;
  std::unique_ptr<QSqlDatabase> db_;
};

} // namespace touka

#endif // DBMANAGER_H
