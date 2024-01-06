//
// Created by Touka on 2024/1/6.
//

#ifndef EVENTDAO_H
#define EVENTDAO_H
#include <QObject>
#include <entity/Event.h>

namespace touka {

class EventDao : public QObject {
public slots:
  // Insert a new event into the database
  virtual bool insertEvent(const Event &event);

  // Get an event from the database
  virtual Event getEvent(int eventId);

  // Get all events from the database
  virtual std::vector<Event> getAllEvents();

  // Get events in a date range from the database
  virtual std::vector<Event> getEventsInRange(const QDate &startDate,
                                              const QDate &endDate);

  // Search events in the database
  virtual std::vector<Event> searchEvents(const QString &query);

  // Update an event in the database
  virtual bool updateEvent(const Event &event);

  // Delete an event from the database
  virtual bool deleteEvent(int eventId);
};

} // touka

#endif //EVENTDAO_H
