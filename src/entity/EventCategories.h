//
// Created by Touka on 2023/12/15.
//

#ifndef EVENTCATEGORIES_H
#define EVENTCATEGORIES_H
#include <utility>

#include "types.hpp"

namespace touka {

class EventCategories {
    Color cate_color_;
    String cate_name_;
    String cate_description_;
public:
    explicit EventCategories(const Color& cate_color, String  cate_name, String  cate_description)
        : cate_color_(cate_color),
          cate_name_(std::move(cate_name)),
          cate_description_(std::move(cate_description)) {
    }

    [[nodiscard]] const Color& getColor() const {
        return cate_color_;
    }

    void setColor(const Color& color) {
        cate_color_ = color;
    }

    [[nodiscard]] const String& getName() const {
        return cate_name_;
    }

    void setName(const String& name) {
        cate_name_ = name;
    }

    [[nodiscard]] const String& getDescription() const {
        return cate_description_;
    }

    void setDescription(const String& description) {
        cate_description_ = description;
    }
};

} // touka

#endif //EVENTCATEGORIES_H
