//
// Created by Touka on 2023/12/13.
//

#ifndef INTELLISCHEDULER_WEEKEVENTCELL_H
#define INTELLISCHEDULER_WEEKEVENTCELL_H

#include <QWidget>
#include "types.hpp"

namespace touka {
    QT_BEGIN_NAMESPACE
    namespace Ui { class WeekEventCell; }
    QT_END_NAMESPACE

    constexpr static int16 HALF_HOUR_HEIGHT_IN_PIXELS = 12;

    class WeekEventCell : public QWidget {
    Q_OBJECT

    public:
        explicit WeekEventCell(QWidget *parent = nullptr);

        ~WeekEventCell() override;

    private:
        Ui::WeekEventCell *ui;
    };
} // touka

#endif //INTELLISCHEDULER_WEEKEVENTCELL_H
