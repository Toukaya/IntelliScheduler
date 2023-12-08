//
// Created by Touka on 2023/12/4.
//

#ifndef MONTHVIEW_H
#define MONTHVIEW_H

#include <QWidget>

#include "types.hpp"

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui { class MonthView; }
QT_END_NAMESPACE

class GridCellWidget;

class MonthView : public QWidget {
Q_OBJECT

public:
    explicit MonthView(QWidget *parent = nullptr);
    ~MonthView() override;

private:
    void setDateLabels();

public slots:

private:
    Ui::MonthView *ui;

    int curr_year_;
    int curr_month_;

};
} // touka

#endif //MONTHVIEW_H
