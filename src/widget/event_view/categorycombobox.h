//
// Created by Touka on 2023/12/20.
//

#ifndef CATEGORYCOMBOBOX_H
#define CATEGORYCOMBOBOX_H

#include <QComboBox>

#include "types.hpp"

namespace touka {
    class EventCategories;

    class CategoryComboBox : public QComboBox {
        Q_OBJECT

    public:
        explicit CategoryComboBox(QWidget* parent = nullptr); 

        void addCategory(const EventCategories &category);

        ~CategoryComboBox() override;

        String currentId() const;

    private:
        std::unordered_map<int, String> cate_idx_to_id_;
    };
} // touka

#endif //CATEGORYCOMBOBOX_H
