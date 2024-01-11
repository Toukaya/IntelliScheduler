//
// Created by Touka on 2023/11/29.
//

#include "Event.h"

#include "controller/AppManager.h"

namespace touka {
  int Event::rowCount(const QModelIndex& parent) const {
    return 1;
  }

  int Event::columnCount(const QModelIndex& parent) const {
    return COLUMN_COUNT;
  }

  QVariant Event::data(const QModelIndex& index, int role) const {
    if (role != Qt::EditRole) return {};
    switch (index.column()) {
      case IdColumn:
        return uid_;
      case SummaryColumn:
        return summary_;
      case DescriptionColumn:
        return description_;
      case StatusColumn:
        return status_;
      case PriorityColumn:
        return priority_;
      case AllDayColumn:
        return all_day_;
      case PrivateColumn:
        return private_;
      case StartTimeColumn:
        return dt_start_;
      case EndTimeColumn:
        return dt_end_;
      case CreatedTimeColumn:
        return created_;
      case LastModifiedTimeColumn:
        return last_modified_;
      case TimeZoneColumn:
        return tz_.id();
      case LocationColumn:
        return location_;
      // case RecurrenceRuleColumns:
      //   return rrule_ ? QVariant(*rrule_) Columns: QVariant();
      case AlarmTimeColumn:
        return alarm_time_ ? QVariant(*alarm_time_) : QVariant();
      case CategoriesColumn:
        return categories_ ? QVariant(categories_->get_cate_name()) : QVariant();
      default:
        return {};
    }
  }

  bool Event::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role != Qt::EditRole) return false;
    switch (index.column()) {
      case SummaryColumn:
        summary_ = value.toString();
        break;
      case DescriptionColumn:
        description_ = value.toString();
        break;
      case StatusColumn:
        status_ = value.value<Status>();
        break;
      case PriorityColumn:
        priority_ = value.value<Priority>();
        break;
      case AllDayColumn:
        all_day_ = value.toBool();
        break;
      case PrivateColumn:
        private_ = value.toBool();
        break;
      case StartTimeColumn:
        dt_start_ = value.toDateTime();
        break;
      case EndTimeColumn:
        dt_end_ = value.toDateTime();
        break;
      case CreatedTimeColumn:
        created_ = value.toDateTime();
        break;
      case LastModifiedTimeColumn:
        last_modified_ = value.toDateTime();
        break;
      case TimeZoneColumn:
        tz_ = QTimeZone(value.toByteArray());
        break;
      case LocationColumn:
        location_ = value.toString();
        break;
      // case RecurrenceRuleColumns:
      //   rrule_ = value.value<Recurrence>();
      //   break;
      case AlarmTimeColumn:
        alarm_time_ = value.toDateTime();
        break;
      case CategoriesColumn:
        categories_ = AppManager::getEvtCategoryByName(value.toString());
        break;
      default:
        return false;
    }
    return true;
  }
} // touka