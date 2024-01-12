//
// Created by Touka on 2023/12/11.
//

#ifndef DATEUTIL_H
#define DATEUTIL_H
#include <unordered_map>

#include "EnumUtils.h"
#include "types.hpp"

#define MONTH_TO_INT_TOUKA EnumUtils::toUnderlying<Month>
#define WEEK_TO_INT_TOUKA EnumUtils::toUnderlying<Week>

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

/**
 * @class DateUtil
 * This class provides utility functions for working with dates.
 */
class DateUtil {
public:
  static bool isValid(int year, Month month, int day);
  /**
   * @brief Returns the literal representation of the given month.
   *
   * This static function takes a Month enumeration value and returns its
   * literal representation as a string.
   *
   * @param month The Month value to get the literal representation for.
   * @return The literal representation of the given month.
   *
   * @sa DateUtil::monthToString
   */
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
      QObject::tr("December")};
  inline static const std::array<QString, 8> weekToString = {
      "",
      QObject::tr("Monday"),
      QObject::tr("Tuesday"),
      QObject::tr("Wednesday"),
      QObject::tr("Thursday"),
      QObject::tr("Friday"),
      QObject::tr("Saturday"),
      QObject::tr("Sunday")};
};

} // namespace touka

#endif // DATEUTIL_H
