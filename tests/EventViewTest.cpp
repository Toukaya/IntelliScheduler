#include <QtTest>
#include <QApplication>
#include <QPaintEvent>
#include <QPainter>

#include "../src/view/eventview.h"

namespace touka {
    class EventViewTest : public QObject
    {
        Q_OBJECT

    private slots:
        void initTestCase()
        {
            widget = new EventView(false);
        }

        void testCase1() {
            widget->show();

            auto pos = widget->pos();
            pos.rx() += widget->width();
            pos.ry() += widget->height() / 2;

            EventView::menu(pos, widget);

            QEventLoop loop;
            QTimer::singleShot(10000, &loop, &QEventLoop::quit);
            loop.exec();
        }

        void cleanupTestCase()
        {
            delete widget;
        }

    private:
        EventView * widget = nullptr;
    };
}

QTEST_MAIN(touka::EventViewTest)
#include "EventViewTest.moc"