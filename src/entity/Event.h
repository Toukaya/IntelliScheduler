//
// Created by Touka on 2023/11/29.
//

#ifndef EVENT_H
#define EVENT_H

#include <utility>
#include <QStandardItemModel>

#include "EventCategories.h"
#include "Recurrence.h"
#include "types.hpp"
#include "utils/EventUtils.h"

namespace touka {

using Id = String;

class Event : public QStandardItemModel {
  Id uid_;
  String summary_;
  String description_;
  Status status_;
  Priority priority_;
  bool all_day_;
  bool private_;

  DateTime dt_start_;
  DateTime dt_end_;
  DateTime created_;
  DateTime last_modified_;
  TimeZone tz_;

  String location_;
  std::optional<Recurrence> rrule_;
  std::optional<DateTime> alarm_time_;

  CategoryPtr categories_;

public:
  enum Columns {
    IdColumn,
    SummaryColumn,
    DescriptionColumn,
    StatusColumn,
    PriorityColumn,
    AllDayColumn,
    PrivateColumn,
    StartTimeColumn,
    EndTimeColumn,
    CreatedTimeColumn,
    LastModifiedTimeColumn,
    TimeZoneColumn,
    LocationColumn,
    RecurrenceRuleColumn,
    AlarmTimeColumn,
    CategoriesColumn,
    COLUMN_COUNT
  };

  [[nodiscard]] int rowCount(const QModelIndex& parent) const override;

  [[nodiscard]] int columnCount(const QModelIndex& parent) const override;

  [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

  bool setData(const QModelIndex& index, const QVariant& value, int role) override;

  Event()
    : summary_(tr("New Event")), status_(Status::CONFIRMED), priority_(Priority::NORMAL),
      all_day_(false), private_(false), categories_(nullptr) {
  }

  Event(Id uid, String summary, String description, Status status,
        Priority priority, bool all_day, bool private_, DateTime dt_start,
        DateTime dt_end, DateTime created,
        DateTime last_modified, TimeZone tz, String location,
        const std::optional<Recurrence> &rrule,
        const std::optional<DateTime> &alarm_time, CategoryPtr categories)
      : uid_(std::move(uid)), summary_(std::move(summary)),
        description_(std::move(description)), status_(status),
        priority_(priority), all_day_(all_day), private_(private_),
        dt_start_(std::move(dt_start)), dt_end_(std::move(dt_end)),
        created_(std::move(created)),
        last_modified_(std::move(last_modified)), tz_(std::move(tz)),
        location_(std::move(location)), rrule_(rrule), alarm_time_(alarm_time),
        categories_(std::move(categories)) {}

  [[nodiscard]] const Id &get_uid() const { return uid_; }

  void set_uid(const Id &uid) { uid_ = uid; }

  [[nodiscard]] const String &get_summary() const { return summary_; }

  void set_summary(const String &summary) { summary_ = summary; }

  [[nodiscard]] const String &get_description() const { return description_; }

  void set_description(const String &description) {
    description_ = description;
  }

  [[nodiscard]] Priority get_priority() const { return priority_; }

  void set_priority(const Priority priority) { priority_ = priority; }

  [[nodiscard]] bool is_all_day() const { return all_day_; }

  void set_all_day(const bool all_day) { all_day_ = all_day; }

  [[nodiscard]] bool is_private() const { return private_; }

  void set_private(const bool private_) { this->private_ = private_; }

  [[nodiscard]] const DateTime &get_dt_start() const { return dt_start_; }

  void set_dt_start(const DateTime &dt_start) { dt_start_ = dt_start; }

  [[nodiscard]] const DateTime &get_dt_end() const { return dt_end_; }

  void set_dt_end(const DateTime &dt_end) { dt_end_ = dt_end; }

  [[nodiscard]] const DateTime &get_created() const { return created_; }

  void set_created(const DateTime &created) { created_ = created; }

  [[nodiscard]] const DateTime &get_last_modified() const {
    return last_modified_;
  }

  void set_last_modified(const DateTime &last_modified) {
    last_modified_ = last_modified;
  }

  [[nodiscard]] const TimeZone &get_tz() const { return tz_; }

  void set_tz(const TimeZone &tz) { tz_ = tz; }

  [[nodiscard]] const String &get_location() const { return location_; }

  void set_location(const String &location) { location_ = location; }

  [[nodiscard]] const std::optional<Recurrence> &get_rrule() const {
    return rrule_;
  }

  void set_rrule(const Recurrence &rrule) { rrule_ = rrule; }

  [[nodiscard]] const std::optional<DateTime> &get_alarm_time() const {
    return alarm_time_;
  }

  void set_alarm_time(const std::optional<DateTime> &alarm_time) {
    alarm_time_ = alarm_time;
  }

  [[nodiscard]] const CategoryPtr &get_categories() const {
    return categories_;
  }

  void set_categories(const CategoryPtr &categories) {
    categories_ = categories;
  }

  void set_status(const Status status) {
    status_ = status;
  }

  [[nodiscard]] Status get_status() const {
    return status_;
  }
};

using EventPtr = std::shared_ptr<Event>;
using EventPtrList = QVector<EventPtr>;

} // namespace touka

#endif // EVENT_H
