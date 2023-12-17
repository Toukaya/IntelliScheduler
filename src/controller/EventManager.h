//
// Created by Touka on 2023/12/15.
//

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <QtCore/QObject>

#include "entity/Event.h"

namespace touka {

class EventManager : public QObject{
    // Q_OBJECT

public:
    static std::vector<Event> parseICalFormat(std::istringstream& icalDataStream);
    static String toICalFormat(const Event &evt);
    static Event iCalFormatToEvt(const String &icalDataStream);
    static String exportICalFormat(const std::vector<Event> &evts);
};

} // touka

#endif //EVENTMANAGER_H
