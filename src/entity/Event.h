//
// Created by Touka on 2023/11/29.
//

#ifndef EVENT_H
#define EVENT_H

#include "EventCategories.h"
#include "Recurrence.h"
#include "types.hpp"
#include "utils/EventUtils.h"

namespace touka {

using Id = String;

class Event {
private:
  Id uid_;
  String summary_;
  String description_;
  Classification classification_;
  Status status_;
  // Transparency transp_;
  Priority priority_;
  DateTime dt_start_;
  DateTime dt_end_;
  DateTime dt_stamp_;
  DateTime created_;
  DateTime last_modified_;
  String location_;
  TimeZone tz_;
  Recurrence rrule_;
  uint8 recurrence_no_;
  std::vector<DateTime> rdate_;

  EventCategories categories_;
  std::shared_ptr<Event> base_evt_;

public:
  [[nodiscard]] const Id &get_uid() const { return uid_; }

  void set_uid(const Id &uid) { uid_ = uid; }

  [[nodiscard]] const String &get_summary() const { return summary_; }

  void set_summary(const String &summary) { summary_ = summary; }

  [[nodiscard]] const String &get_description() const { return description_; }

  void set_description(const String &description) {
    description_ = description;
  }

  [[nodiscard]] Classification get_classification() const {
    return classification_;
  }

  void set_classification(const Classification classification) {
    classification_ = classification;
  }

  [[nodiscard]] Status get_status() const { return status_; }

  void set_status(const Status status) { status_ = status; }

  // [[nodiscard]] Transparency get_transp() const {
  //     return transp_;
  // }
  //
  // void set_transp(const Transparency transp) {
  //     transp_ = transp;
  // }

  [[nodiscard]] Priority get_priority() const { return priority_; }

  void set_priority(const Priority priority) { priority_ = priority; }

  [[nodiscard]] const DateTime &get_dt_start() const { return dt_start_; }

  void set_dt_start(const DateTime &dt_start) { dt_start_ = dt_start; }

  [[nodiscard]] const DateTime &get_dt_end() const { return dt_end_; }

  void set_dt_end(const DateTime &dt_end) { dt_end_ = dt_end; }

  [[nodiscard]] const DateTime &get_dt_stamp() const { return dt_stamp_; }

  void set_dt_stamp(const DateTime &dt_stamp) { dt_stamp_ = dt_stamp; }

  [[nodiscard]] const DateTime &get_created() const { return created_; }

  void set_created(const DateTime &created) { created_ = created; }

  [[nodiscard]] const DateTime &get_last_modified() const {
    return last_modified_;
  }

  void set_last_modified(const DateTime &last_modified) {
    last_modified_ = last_modified;
  }

  [[nodiscard]] const String &get_location() const { return location_; }

  void set_location(const String &location) { location_ = location; }

  [[nodiscard]] const TimeZone &get_tz() const { return tz_; }

  void set_tz(const TimeZone &tz) { tz_ = tz; }

  [[nodiscard]] const Recurrence &get_rrule() const { return rrule_; }

  void set_rrule(const Recurrence &rrule) { rrule_ = rrule; }

  [[nodiscard]] uint8 get_recurrence_no() const { return recurrence_no_; }

  void set_recurrence_no(const uint8 recurrence_no) {
    recurrence_no_ = recurrence_no;
  }

  [[nodiscard]] const std::vector<DateTime> &get_rdate() const {
    return rdate_;
  }

  void set_rdate(const std::vector<DateTime> &rdate) { rdate_ = rdate; }

  [[nodiscard]] const EventCategories &get_categories() const {
    return categories_;
  }

  void set_categories(const EventCategories &categories) {
    categories_ = categories;
  }

  [[nodiscard]] const std::shared_ptr<Event> &get_base_evt() const {
    return base_evt_;
  }

  void set_base_evt(const std::shared_ptr<Event> &base_evt) {
    base_evt_ = base_evt;
  }
};

} // namespace touka

#endif // EVENT_H
