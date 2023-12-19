//
// Created by Touka on 2023/12/20.
//

#ifndef CATEGORYCOMBOBOX_H
#define CATEGORYCOMBOBOX_H

#include <QComboBox>

namespace touka {
    class EventCategories;

    class CategoryComboBox : public QComboBox {
        Q_OBJECT

    public:
        explicit CategoryComboBox(QWidget* parent = nullptr);

        void addCategory(const EventCategories &category);

        ~CategoryComboBox() override;
    };
} // touka

#endif //CATEGORYCOMBOBOX_H
