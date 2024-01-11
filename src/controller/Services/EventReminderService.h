//
// Created by Touka on 2024/1/10.
//

#ifndef EVENTREMINDERSERVICE_H
#define EVENTREMINDERSERVICE_H

#include <QObject>
#include <queue>

#include "entity/Event.h"

namespace touka {

class EventReminderService : public QObject {
  Q_OBJECT

public:
  explicit EventReminderService(QObject *parent = nullptr);
  ~EventReminderService() override;

signals:
  void eventReminder(const EventPtr &evt);

public slots:
  void updateTodayEvents(const EventPtrList &events);

  void addEvent(const EventPtr &evt);

protected slots:
  void checkReminders();

private:
  std::map<QTime, EventPtrList, std::greater<>> today_events_;
  std::unique_ptr<QTimer> timer_;
};
} // namespace touka

#endif // EVENTREMINDERSERVICE_H
