//
// Created by Touka on 2023/11/29.
//

#ifndef EVENT_H
#define EVENT_H

#include "../types.hpp"

namespace touka {

using Id = uint32;

class Event {

private:

    Id id_;

    String summary_;

    String description_;

    String location_;

    Vector<std::pair<DateTime, DateTime>> dateTime_;

public:
    [[nodiscard]] Id get_id() const {
        return id_;
    }

    [[nodiscard]] const String& get_summary() const {
        return summary_;
    }

    [[nodiscard]] const String& get_description() const {
        return description_;
    }

    [[nodiscard]] const String& get_location() const {
        return location_;
    }

    [[nodiscard]] const Vector<std::pair<DateTime, DateTime>>& get_date_time() const {
        return dateTime_;
    }
};

} // touka

#endif //EVENT_H
