//
// Created by Touka on 2023/12/8.
//

#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <QFrame>
#include <QtCore/qdatetime.h>

#include "types.hpp"

namespace touka {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class GridCell;
    }
    QT_END_NAMESPACE

    class Event;

    constexpr static std::string_view OMITTED_EVT_LABEL_COLOR = "#848484";

    constexpr static QColor WEEKEND_BACKGROUND_COLOR(243, 243, 243);

    constexpr static QColor COMMON_CELL_TEXT_COLOR(44, 44, 44);

    constexpr static QColor NOT_ACTIVATED_CELL_TEXT_COLOR(44, 44, 44, 88);

    constexpr static QColor WEEKEND_CELL_TEXT_COLOR(134, 134, 134);

    class GridCell : public QFrame {
        Q_OBJECT

    public:
        explicit GridCell(QWidget *parent = nullptr);
        explicit GridCell(const Date &date, QWidget *parent = nullptr);
        ~GridCell() override;

        void setDate(const Date &date);

        [[nodiscard]] bool isActivate() const;

        void setActivate(bool isActivate);

        [[nodiscard]] inline bool isWeekend() const;

    protected:
        // void mouseReleaseEvent(QMouseEvent* event) override;

        void contextMenuEvent(QContextMenuEvent* event) override;

    public slots:
        void refresh();

        void updateEvent(const Event &evt);

        void selectOut() const;

        void onActionNewEvt() const;

        void onActionDelete() const;

    private:
        Ui::GridCell *ui;
        Date date_;
        bool is_activate_;

        void applyTextColor(const QColor &color) const;

        void setDayOfMonthText(bool showMonthStr = false) const;
        void setWeekendStyles();
        void setCurrentDayStyles() const;

    private slots:
        // void onEvtClicked(bool )
    };
}  // namespace touka

#endif  // GRIDCELL_H
