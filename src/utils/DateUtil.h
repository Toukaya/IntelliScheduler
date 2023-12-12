//
// Created by Touka on 2023/12/11.
//

#ifndef DATEUTIL_H
#define DATEUTIL_H
#include <unordered_map>

#include "types.hpp"

namespace touka {

    enum class Month {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };
    enum class Week {
        Monday = 1,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

class DateUtil {
public:
    static bool isValid(int year, Month month, int day);

    static String getLiteralMonth(Month month);

    static String getLiteralWeek(Week week);

    static Date getCurrDate();
    static int getDaysInMonth(int year, Month month);
    static Date getFirstDayOfMonth(const Date &date);
    static Date getLastDayOfMonth(const Date &date);
    static bool isLeap(int year);
    static Date increaseYear(const Date &date, int numOfYears);
    static Date decreaseYear(const Date &date, int numOfYears);
    static Date increaseMonth(const Date &date, int numOfMonths);
    static Date decreaseMonth(const Date &date, int numOfMonths);
    static Date increaseDay(const Date &date, int numOfDays);
    static Date decreaseDay(const Date &date, int numOfDays);

private:
    inline static const std::array<QString, 13> monthToString = {
        "",
        QObject::tr("January"),
        QObject::tr("February"),
        QObject::tr("March"),
        QObject::tr("April"),
        QObject::tr("May"),
        QObject::tr("June"),
        QObject::tr("July"),
        QObject::tr("August"),
        QObject::tr("September"),
        QObject::tr("October"),
        QObject::tr("November"),
        QObject::tr("December")
    };
    inline static const  std::array<QString, 8> weekToString = {
        "",
        QObject::tr("Monday"),
        QObject::tr("Tuesday"),
        QObject::tr("Wednesday"),
        QObject::tr("Thursday"),
        QObject::tr("Friday"),
        QObject::tr("Saturday"),
        QObject::tr("Sunday")
      };
};

} // touka

#endif //DATEUTIL_H