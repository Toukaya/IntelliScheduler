//
// Created by Touka on 2024/1/10.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_EventReminderService.h" resolved

#include "EventReminderService.h"

#include <QTimer>

#include "AppConfig.hpp"

namespace touka {

constexpr int REMINDER_CHECK_INTERVAL_SEC = 60; // Check every minute

EventReminderService::EventReminderService(QObject *parent)
    : QObject(parent), timer_(std::make_unique<QTimer>(this)) {
  connect(timer_.get(), &QTimer::timeout, this,
          &EventReminderService::checkReminders);
  timer_->setInterval(REMINDER_CHECK_INTERVAL_SEC * 1000);
}

EventReminderService::~EventReminderService() = default;

void EventReminderService::updateTodayEvents(const EventPtrList &events) {
  timer_->stop();
  today_events_.clear();
  const auto now = DateTime::currentDateTime();
  for (const auto &evt : events) {
    const auto time = evt->get_alarm_time();
    if (!time || time <= now)
      continue;
    today_events_[time->time()].push_back(evt);
  }
  timer_->start();
}

void EventReminderService::addEvent(const EventPtr &evt) {
  if (!evt) return;
  const auto time = evt->get_alarm_time();
  const auto now = QTime::currentTime();
  if (!time || time->time() <= now)
    return;
  today_events_[time->time()].push_back(evt);
}

void EventReminderService::checkReminders() {
  const auto now = QTime::currentTime();
  const auto next = now.addSecs(REMINDER_CHECK_INTERVAL_SEC);
  auto it = today_events_.begin();
  while (it != today_events_.end() && it->first <= next) {
    for (const auto &evt : it->second) {
      if (!evt)
        continue;
      const auto trayIcon = AppConfig::getTrayIcon();
      trayIcon->showMessage(evt->get_summary(), evt->get_description(),
                            QSystemTrayIcon::Information, 10000);
      emit eventReminder(evt);
    }
    it = today_events_.erase(it);
  }
}
} // namespace touka
