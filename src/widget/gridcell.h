//
// Created by Touka on 2023/12/8.
//

#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <QFrame>

#include "types.hpp"

namespace touka {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class GridCell;
    }
    QT_END_NAMESPACE
    class Event;

    constexpr static std::string_view OMITTED_EVT_LABEL_COLOR = "#848484";

    class GridCell : public QFrame {
        Q_OBJECT

    public:
        explicit GridCell(QWidget *parent = nullptr);
        ~GridCell() override;

        void setDate(const Date &date) const;

    public slots:
         void updateEvent(const Event &evt);

    private:
        Ui::GridCell *ui;
        std::shared_ptr<Date> date_;

    private slots:
        // void onEvtClicked(bool )
    };
}  // namespace touka

#endif  // GRIDCELL_H
