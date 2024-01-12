//
// Created by Touka on 2023/12/15.
//

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

// #include <async_simple/coro/Lazy.h>

#include "Services/EventReminderService.h"
#include "Services/EventService.h"
#include "db/DBManager.h"
#include "types.hpp"

class QSignalMapper;

namespace touka {

class AppManager : public QObject {
  Q_OBJECT

public:
  static AppManager &instance();

  static CategoryPtrList getEvtCategories();

  static CategoryPtr getEvtCategoryById(const char *categoryId);

  static CategoryPtr getEvtCategoryByName(const String &categoryName);

  static EventPtr
  createEmptyEvt(const std::optional<DateTime> &startTime = std::nullopt);

  // // TODO inplement getCategorisedSchedule param: lastMonthBusySchedule
  // static std::vector<Event>
  // getCategorisedSchedule(const std::vector<Event> &events);
  // // TODO inplement initialiseHistFreqs param: category
  // static std::vector<Event>
  // initialiseHistFreqs(const std::vector<Event> &events);
  // // TODO implement getHistFreqs param: category
  // static std::vector<Event> getHistFreqs(const std::vector<Event> &events);

signals:
  void eventAdded(const EventPtr &evt);
  void eventDeleted(const EventPtr &evt);
  void eventModified(const EventPtr &oldEvent, const EventPtr &newEvent);

  void categoryAdded(const CategoryPtr &category);
  void categoryDeleted(const CategoryPtr &category);
  void categoryModified(const CategoryPtr &oldCategory,
                        const CategoryPtr &newCategory);

  void reminderTriggered(const EventPtr &evt);

public slots:
  void addEvent(const EventPtr &evt);
  void deleteEvent(const EventPtr &evt);
  void deleteEvent(const char *uid);
  void modifyEvent(const EventPtr &oldEvent, const EventPtr &newEvent);
  EventPtr getEventById(const String &eventId);
  EventPtrList getEventsOfDay(const Date &date);
  EventPtrList getEventsOfWeek(const Date &date);
  EventPtrList getEventsOfMonth(const Date &date);
  EventPtrList getEventsInInterval(const DateTime &start, const DateTime &end);
  EventPtrList getEventsOfCategory(const EventCategories *category);
  EventPtrList getEventsByName(const char *eventName);
  EventPtr getEventByNameAndTime(const char *eventName,
                                 const DateTime &startTime);

private:
  explicit AppManager(QObject *parent = nullptr);
  ~AppManager() override = default;

  EventService eventService_;
  EventReminderService reminderService_;
  static DBManager db_manager_;

public:
  AppManager(const AppManager &) = delete;
  AppManager(AppManager &&) = delete;
  AppManager &operator=(const AppManager &) = delete;
  AppManager &operator=(AppManager &&other) = delete;
};

} // namespace touka

#endif // EVENTMANAGER_H
