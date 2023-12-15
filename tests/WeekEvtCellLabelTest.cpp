//
// Created by Touka on 2023/12/14.
//

#include <QtTest>
#include <QApplication>
#include "widget/weekevtcelllabel.h"

namespace touka {
    class WeekEvtCellLabelTest : public QObject
    {
        Q_OBJECT

    private slots:
        void initTestCase()
        {
            widget = new WeekEvtCellLabel();
        }

        void testCase1() {
            widget->setColor(Qt::green);
            widget->show();

            QEventLoop loop;
            QTimer::singleShot(10000, &loop, &QEventLoop::quit);
            loop.exec();
        }

        void cleanupTestCase()
        {
            delete widget;
        }

    private:
        WeekEvtCellLabel * widget = nullptr;
    };
}



QTEST_MAIN(touka::WeekEvtCellLabelTest)
#include "WeekEvtCellLabelTest.moc"