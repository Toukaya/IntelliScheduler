//
// Created by Touka on 2023/12/15.
//

#ifndef EVENTCATEGORIES_H
#define EVENTCATEGORIES_H
#include <QStandardItemModel>
#include <utility>

#include "types.hpp"

namespace touka {

class EventCategories : public QStandardItemModel {
  String cate_id_;
  Color cate_color_;
  String cate_name_;

public:
  enum Columns {
    IdColumn,
    ColorColumn,
    NameColumn,
    COLUMN_COUNT
  };

  [[nodiscard]] int rowCount(const QModelIndex& parent) const override;

  [[nodiscard]] int columnCount(const QModelIndex& parent) const override;

  [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

  bool setData(const QModelIndex& index, const QVariant& value, int role) override;

  EventCategories(String cate_id, const Color& cate_color, String cate_name)
    : cate_id_(std::move(cate_id)),
      cate_color_(cate_color),
      cate_name_(std::move(cate_name)) {
  }

  [[nodiscard]] String get_cate_id() const {
    return cate_id_;
  }

  [[nodiscard]] const Color& get_cate_color() const {
    return cate_color_;
  }

  [[nodiscard]] const String& get_cate_name() const {
    return cate_name_;
  }

  void set_cate_id(String cate_id) {
    cate_id_ = std::move(cate_id);
  }

  void set_cate_color(const Color& cate_color) {
    cate_color_ = cate_color;
  }

  void set_cate_name(const String& cate_name) {
    cate_name_ = cate_name;
  }

  // TODO remove it
  [[nodiscard]] const Color &getColor() const { return cate_color_; }

  void setColor(const Color &color) { cate_color_ = color; }

  [[nodiscard]] const String &getName() const { return cate_name_; }

  void setName(const String &name) { cate_name_ = name; }

};

  using Categroy = EventCategories;
  using CategoryPtr = std::shared_ptr<Categroy>;
  using CategoryPtrList = std::vector<CategoryPtr>;

} // namespace touka

#endif // EVENTCATEGORIES_H
