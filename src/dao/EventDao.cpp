//
// Created by Touka on 2024/1/6.
//

#include "EventDao.h"
#include "utils/DBUtil.h"

namespace touka {
    bool EventDao::insertEvent(const Event& event) {
    }

    Event EventDao::getEvent(int eventId) {
    }

    std::vector<Event> EventDao::getAllEvents() {
    }

    std::vector<Event> EventDao::getEventsInRange(const QDate& startDate, const QDate& endDate) {
    }

    std::vector<Event> EventDao::searchEvents(const QString& query) {
    }

    bool EventDao::updateEvent(const Event& event) {
    }

    bool EventDao::deleteEvent(int eventId) {
    }
} // touka