//
// Created by Touka on 2024/1/7.
//

#ifndef EVENTSUBSCRIPTIONSERVICE_H
#define EVENTSUBSCRIPTIONSERVICE_H

#include "types.hpp"

class QObject;

namespace touka {

class EventSubscriptionService {
public:
  void subscribe(const String &eventId, const QObject *receiver,
                 const char *method);
};

} // touka

#endif //EVENTSUBSCRIPTIONSERVICE_H
