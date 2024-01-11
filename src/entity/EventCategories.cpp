//
// Created by Touka on 2023/12/15.
//

#include "EventCategories.h"

namespace touka {
  int EventCategories::rowCount(const QModelIndex& parent) const {
    return 1;
  }

  int EventCategories::columnCount(const QModelIndex& parent) const {
    return COLUMN_COUNT;
  }

  QVariant EventCategories::data(const QModelIndex& index, int role) const {
    if (role != Qt::EditRole) return {};
    switch (index.column()) {
      case IdColumn:
        return cate_id_;
      case ColorColumn:
        return cate_color_;
      case NameColumn:
        return cate_name_;
      default:
        return {};
    }
  }

  bool EventCategories::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role != Qt::EditRole) return false;
    switch (index.column()) {
      case ColorColumn:
        cate_color_ = value.value<Color>();
        return true;
      case NameColumn:
        cate_name_ = value.toString();
        return true;
      default:
        return false;
    }
  }
} // touka