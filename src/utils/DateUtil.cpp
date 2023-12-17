//
// Created by Touka on 2023/12/11.
//

#include "DateUtil.h"

#include <QtCore/qdatetime.h>

namespace touka {
    inline bool DateUtil::isValid(int year, Month month, int day) {
        return QDate::isValid(year, MONTH_TO_INT_TOUKA(month), day);
    }

    String DateUtil::getLiteralMonth(Month month) {
        return monthToString.at(MONTH_TO_INT_TOUKA(month));
    }

    String DateUtil::getLiteralWeek(Week week) {
        return weekToString.at(WEEK_TO_INT_TOUKA(week));
    }

    inline Date DateUtil::getCurrDate() {
        return QDate::currentDate();
    }

    inline int DateUtil::getDaysInMonth(int year, Month month) {
        return QDate(year, MONTH_TO_INT_TOUKA(month), 1).daysInMonth();
    }

    inline Date DateUtil::getFirstDayOfMonth(const Date &date) {
        return {date.year(), date.month(), 1};
    }

    inline Date DateUtil::getLastDayOfMonth(const Date &date) {
        return {date.year(), date.month(), date.daysInMonth()};
    }

    inline bool DateUtil::isLeap(int year){
        return QDate::isLeapYear(year);
    }

    inline Date DateUtil::increaseMonth(const Date &date, int numOfMonths) {
        return date.addMonths(numOfMonths);
    }

    inline Date DateUtil::decreaseMonth(const Date &date, int numOfMonths){
        return date.addMonths(-numOfMonths);
    }

    inline Date DateUtil::increaseDay(const Date &date, int numOfDays){
        return date.addDays(numOfDays);;
    }

    inline Date DateUtil::decreaseDay(const Date &date, int numOfDays){
        return date.addDays(-numOfDays);;
    }

    inline Date DateUtil::increaseYear(const Date &date, int numOfYears){
        return date.addYears(numOfYears);
    }

    inline Date DateUtil::decreaseYear(const Date &date, int numOfYears){
        return date.addYears(-numOfYears);
    }
} // touka