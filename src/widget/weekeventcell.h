//
// Created by Touka on 2023/12/13.
//

#ifndef INTELLISCHEDULER_WEEKEVENTCELL_H
#define INTELLISCHEDULER_WEEKEVENTCELL_H

#include <QWidget>
#include <unordered_set>
#include "types.hpp"

namespace touka {
    class Event;
    QT_BEGIN_NAMESPACE
    namespace Ui { class WeekEventCell; }
    QT_END_NAMESPACE

    class WeekEvtCellLabel;

    constexpr static int16 HALF_HOUR_HEIGHT_IN_PIXELS = 30;

    class WeekEventCell : public QWidget {
    Q_OBJECT

    public:
        explicit WeekEventCell(QWidget *parent = nullptr);

        ~WeekEventCell() override;

        void update();

        void addEvent(const std::shared_ptr<Event>& evt);

        void removeEvent(std::shared_ptr<Event> evt);

    protected:

        bool inRect(QPoint pos, QRect &rect);

        void clear();

    private:
        Ui::WeekEventCell *ui;

        std::unordered_set<std::shared_ptr<Event>> week_evt_cell_labels_;
    };
} // touka

#endif //INTELLISCHEDULER_WEEKEVENTCELL_H
