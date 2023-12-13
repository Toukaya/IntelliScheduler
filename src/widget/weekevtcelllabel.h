//
// Created by Touka on 2023/12/13.
//

#ifndef INTELLISCHEDULER_WEEKEVTCELLLABEL_H
#define INTELLISCHEDULER_WEEKEVTCELLLABEL_H

#include <QLabel>

namespace touka {
    QT_BEGIN_NAMESPACE
    namespace Ui { class WeekEvtCellLabel; }
    QT_END_NAMESPACE

    class WeekEvtCellLabel : public QLabel {
    Q_OBJECT

    public:
        explicit WeekEvtCellLabel(QWidget *parent = nullptr);

        ~WeekEvtCellLabel() override;

    private:
        Ui::WeekEvtCellLabel *ui;
    };
} // touka

#endif //INTELLISCHEDULER_WEEKEVTCELLLABEL_H
