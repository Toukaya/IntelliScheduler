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
enum class Month;

class MonthView : public QWidget {
Q_OBJECT

public:
    explicit MonthView(QWidget *parent = nullptr);

    ~MonthView() override;

    Date getCurrentMonthFirstDay();

protected:

    void initTable() const;

    void initDateLabels();


    void updateDateLabels();

public slots:

    void refresh();

    void navigateTo(int year, Month month);

private:
    Ui::MonthView *ui;

    int curr_year_;

    Month curr_month_;

    [[nodiscard]] QString getDateTitle() const;

};
} // touka

#endif //MONTHVIEW_H
