//
// Created by Touka on 2023/12/15.
//

#ifndef EVENTCATEGORIES_H
#define EVENTCATEGORIES_H
#include "types.hpp"

namespace touka {

class EventCategories {
    Color cate_color_;
public:
    [[nodiscard]] const Color& getColor() const {
        return cate_color_;
    }

    void setColor(const Color& color) {
        cate_color_ = color;
    }
};

} // touka

#endif //EVENTCATEGORIES_H
