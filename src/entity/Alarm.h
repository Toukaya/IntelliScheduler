//
// Created by Touka on 2023/12/15.
//

#ifndef ALARM_H
#define ALARM_H
#include "types.hpp"

namespace touka {
    class Alarm {
    public:
        Alarm();

        ~Alarm();

        void setAlarmTime(const DateTime&alarmTime);

        DateTime getAlarmTime() const;

        void setAlarmDescription(const String&alarmDescription);

        String getAlarmDescription() const;

        void setAlarmDuration(int alarmDuration);

        int getAlarmDuration() const;

        void setAlarmRepeatInterval(int alarmRepeatInterval);

        int getAlarmRepeatInterval() const;

    private:
        DateTime alarmTime;
        String alarmDescription;
        int alarmDuration;
        int alarmRepeatInterval;
        String alarmSound;
    };
} // touka

#endif //ALARM_H
