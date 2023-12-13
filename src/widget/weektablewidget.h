//
// Created by Touka on 2023/12/13.
//

#ifndef INTELLISCHEDULER_WEEKTABLEWIDGET_H
#define INTELLISCHEDULER_WEEKTABLEWIDGET_H

#include <QTableWidget>

namespace touka {
    QT_BEGIN_NAMESPACE
    namespace Ui { class WeekTableWidget; }
    QT_END_NAMESPACE

    class ScanLineWidget;

    class WeekTableWidget : public QTableWidget {
    Q_OBJECT

    public:
        explicit WeekTableWidget(QWidget *parent = nullptr);

        ~WeekTableWidget() override;

    protected:
        void paintEvent(QPaintEvent *e) override;

    private:
        Ui::WeekTableWidget *ui;

        int scan_line_pos_;
    };
} // touka

#endif //INTELLISCHEDULER_WEEKTABLEWIDGET_H
