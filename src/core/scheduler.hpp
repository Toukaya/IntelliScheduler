//
// Created by Touka on 2023/11/29.
//

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include <vector>

#include "entity/Event.h"

namespace Core::Scheduler {
    
    struct SchedulingOptions {
        const bool allowOverlap;
    };

    struct ScheduleResult {
        // std::vector<std::pair<Event, std::optional<TimePoint>>> scheduledEvents;
        // std::vector<std::string> errors;
    };

    inline ScheduleResult scheduleEvents(
        const std::vector<touka::Event>&unscheduledEvents,
        const std::vector<touka::Event>&scheduledEvents,
        const SchedulingOptions&options,
        TimePoint startTime,
        TimePoint endTime) noexcept {
    }

    //scheduledEvents
}

#endif //SCHEDULER_HPP
