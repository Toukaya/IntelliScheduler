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

enum class Month;

class MonthView : public QWidget {
Q_OBJECT

public:
    explicit MonthView(QWidget *parent = nullptr);

    ~MonthView() override;

    Date getCurrentMonthFirstDay();

protected:

    /**
     * @brief Initializes the table widget for displaying the month view.
     *
     * This function sets up the table widget to display the month view. It sets the number
     * of rows and columns, adjusts the header sizes, and sets the size policy to allow expanding.
     *
     * @note This function is const, meaning it does not modify the state of the object.
     */
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
