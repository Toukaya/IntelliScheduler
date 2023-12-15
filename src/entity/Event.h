//
// Created by Touka on 2023/11/29.
//

#ifndef EVENT_H
#define EVENT_H

#include <qdatetime.h>

#include "EventCategories.h"
#include "Recurrence.h"
#include "types.hpp"

namespace touka {

using Id = String;

class Event {

private:

    Id uid_;

    String summary_;

    String description_;

    String location_;

    EventCategories categories_;

    DateTime dt_start_;

    DateTime dt_end_;

    DateTime dt_stamp_;

    Recurrence rrule_;

    uint8 recurrence_no_;

    std::shared_ptr<Event> base_evt_;


public:
    [[nodiscard]] Id getUid() const {
        return uid_;
    }

    [[nodiscard]] const String& getSummary() const {
        return summary_;
    }

    [[nodiscard]] const String& getDescription() const {
        return description_;
    }

    [[nodiscard]] const String& getLocation() const {
        return location_;
    }

    [[nodiscard]] DateTime getDtStart() const { return dt_start_; }
    [[nodiscard]] DateTime getDtEnd() const { return dt_end_; }
    [[nodiscard]] DateTime getDtStamp() const { return dt_stamp_; }
    [[nodiscard]] EventCategories getCategories() const { return categories_; }

};

} // touka

#endif //EVENT_H
