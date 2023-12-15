//
// Created by Touka on 2023/12/14.
//

#include <QtTest>
#include <QApplication>
#include <QLabel>
#include <QtWidgets/QVBoxLayout>

#include "widget/weekevtcelllabel.h"
#include "widget/weektablewidget.h"
#include "widget/gridview.h"

namespace touka {
    class WeekTableWidgetTest : public QObject
    {
        Q_OBJECT

    private slots:
        // 在每个测试函数运行前执行的函数
        void initTestCase()
        {
            widget = new WeekTableWidget();
        }

        void testCase1() {
            widget->show();

            // QEventLoop loop;
            // QTimer::singleShot(1000, &loop, &QEventLoop::quit);
            // loop.exec();
        }

        static void testCase2() {
            auto table = std::make_unique<WeekTableWidget>(); // create a 5x5 QTableWidget
            table->setSelectionMode(QAbstractItemView::NoSelection); // disable selection

            // create QLabel with 50% transparent black background
            auto label = std::make_unique<WeekEvtCellLabel>();
            label->setColor(Qt::green);

            // set QLabel as the widget for the central cell
            table->setCellWidget(1, 1, label.get());

            // make the QLabel span 3 rows and 3 columns
            table->setSpan(1, 1, 3, 3);

            // Add table to layout
            auto layout = std::make_unique<QVBoxLayout>();
            layout->addWidget(table.get());

            table->show();

            QEventLoop loop;
            QTimer::singleShot(10000, &loop, &QEventLoop::quit);
            loop.exec();
        }

        static void testCase3() {
            GridView t(5, 5, 0 ,20);

            t.show();

            QEventLoop loop;
            QTimer::singleShot(10000, &loop, &QEventLoop::quit);
            loop.exec();
        }



        void cleanupTestCase()
        {
            delete widget;
        }

    private:
        WeekTableWidget * widget = nullptr;
    };
}



QTEST_MAIN(touka::WeekTableWidgetTest)
#include "WeekTableWidgetTest.moc"