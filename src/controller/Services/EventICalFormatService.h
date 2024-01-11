//
// Created by Touka on 2024/1/7.
//

#ifndef EVENTICALFORMATSERVICE_H
#define EVENTICALFORMATSERVICE_H

#include "types.hpp"

namespace touka {
    class Event;

    class EventFormatService {
    public:
        static std::vector<Event> parseICalFormat(std::istringstream &icalDataStream);
        static String toICalFormat(const Event &evt);
        static Event iCalFormatToEvt(const String &icalDataStream);
        static String exportICalFormat(const std::vector<Event> &evts);
    };

} // touka

#endif //EVENTICALFORMATSERVICE_H
