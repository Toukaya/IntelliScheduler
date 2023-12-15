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
    static Event parseICalFormat(const String &icalData);
    static String exportICalFormat(const Event &evt);
};

} // touka

#endif //EVENTMANAGER_H
