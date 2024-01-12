//
// Created by Touka on 2024/1/10.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_EventReminderService.h" resolved

#include "EventReminderService.h"

#include <QTimer>

// #include "AppConfig.hpp"

namespace touka {

constexpr int REMINDER_CHECK_INTERVAL_SEC = 60; // Check every minute

EventReminderService::EventReminderService(QObject *parent)
    : QObject(parent), timer_(new QTimer(this)) {
  connect(timer_, &QTimer::timeout, this,
          &EventReminderService::checkReminders);

  timer_->setInterval(REMINDER_CHECK_INTERVAL_SEC * 1000);
}

EventReminderService::~EventReminderService() = default;

void EventReminderService::updateTodayEvents(const EventPtrList &events) {
  timer_->stop();
  today_events_.clear();
  const auto today = QDate::currentDate();
  for (const auto &evt : events) {
    if (!evt) continue;
    const auto time = evt->get_alarm_time();
    if (!time || time->date() != today)
      continue;
    today_events_[time->time()].push_back(evt);
  }
  timer_->start();
  checkReminders();
}

void EventReminderService::addEvent(const EventPtr &evt) {
  if (!evt) return;
  const auto time = evt->get_alarm_time();
  const auto next = QTime::currentTime().addSecs(-REMINDER_CHECK_INTERVAL_SEC);
  if (!time || time->time() <= next)
    return;
  today_events_[time->time()].push_back(evt);
}

void EventReminderService::checkReminders() {
  auto now = QTime::currentTime();
  now = QTime(now.hour(), now.minute(), 0, 0);
  const auto next = now.addSecs(REMINDER_CHECK_INTERVAL_SEC);
  for (auto it = today_events_.begin(); it != today_events_.end();) {
    if (it->first > next) break;
    if (it->first < now) {
      it = today_events_.erase(it);
      continue;
    }
    for (const auto &e : it->second) {
      if (!e) continue;
      // const auto trayIcon = AppConfig::getTrayIcon();
      // trayIcon->showMessage(e->get_summary(), e->get_description(),
      //                       QSystemTrayIcon::Information, 10000);
      emit eventReminder(e);
    }
    ++it;
  }
}
} // namespace touka
