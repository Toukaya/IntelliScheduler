//
// Created by Touka on 2023/11/29.
//

#ifndef TYPES_HPP
#define TYPES_HPP

#include <QApplication>
#include <QTime>
#include <QDate>
#include <QtCore/qstring.h>
#include <QtCore/qtimezone.h>

namespace touka {

    using int8 = signed char;
    using int16 = signed short;
    using int32 = signed int;
    using uint8 = unsigned char;
    using uint16 = unsigned short;
    using uint32 = unsigned int;

    using String = QString;
    using DateTime = QDateTime;
    using Date = QDate;
    using Time = QTime;
    using TimeZone = QTimeZone;

    using Color = QColor;

    template <typename T>
    using Vector = QVector<T>;

    constexpr static int16 MINUTES_PER_DAY = 1440;

}

#endif //TYPES_HPP
