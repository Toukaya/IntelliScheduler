//
// Created by Touka on 2023/12/15.
//

#ifndef IEVENTSUBSCRIBER_H
#define IEVENTSUBSCRIBER_H
#include <QtCore/QObject>

namespace touka {
    class Event;

    class IEventSubscriber : public QObject{
        Q_OBJECT
    public slots:
        virtual void onUpdateEvent(const Event &evt) = 0;
        virtual void onNewEvent(const Event &evt) = 0;
        virtual void onRemoveEvent(const Event &evt) = 0;
    };

} // touka

#endif //IEVENTSUBSCRIBER_H
