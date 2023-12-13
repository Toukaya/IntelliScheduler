//
// Created by Touka on 2023/12/13.
//

#ifndef INTELLISCHEDULER_WEEKVIEW_H
#define INTELLISCHEDULER_WEEKVIEW_H

#include <QWidget>

namespace touka {
    QT_BEGIN_NAMESPACE
    namespace Ui { class WeekView; }
    QT_END_NAMESPACE

    enum class Month;
    enum class Week;

    class WeekView : public QWidget {
    Q_OBJECT

    public:
        explicit WeekView(QWidget *parent = nullptr);

        ~WeekView() override;

    public slots:

        void refresh();

        void navigateTo(int year, Month month,  Week week);

    private:
        Ui::WeekView *ui;

        void initTable();

        void scanLineUpdate();
    };
} // touka

#endif //INTELLISCHEDULER_WEEKVIEW_H
