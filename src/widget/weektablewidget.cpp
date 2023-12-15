//
// Created by Touka on 2023/12/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WeekTableWidget.h" resolved

#include "weektablewidget.h"
#include "ui_WeekTableWidget.h"
#include <QTimer>
#include <QPainter>
#include <QScrollBar>
#include <QTime>

#define ViewportHeight MINUTES_PER_DAY

namespace touka {

    WeekTableWidget::WeekTableWidget(QWidget *parent) :
            QTableWidget(parent), ui(new Ui::WeekTableWidget) {
        ui->setupUi(this);

        setShowGrid(false);
        setRowCount(24);
        setColumnCount(7);
        verticalHeader()->setDefaultSectionSize(GRID_HEIGHT);

        auto currTime = QTime::currentTime();
        scan_line_pos_ = currTime.hour() * 60 + currTime.minute();
        todays_num_of_weeks_ = QDate::currentDate().dayOfWeek();

        int secToNextMin = 60 - currTime.second();
        auto timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &WeekTableWidget::updateScanLinePosition);

        // Start the timer to trigger after secToNextMin seconds,
        // then once every minute after that.
        timer->start(1000 * secToNextMin);
        QTimer::singleShot(secToNextMin * 1000, [timer](){ timer->start(TIMER_RESTART_INTERVAL_MSEC); });
    }

    WeekTableWidget::~WeekTableWidget() {
        delete ui;
    }

    bool WeekTableWidget::viewportEvent(QEvent *event) {
        if (event->type() != QEvent::Paint)
            return QTableWidget::viewportEvent(event);
        bool ret = QTableWidget::viewportEvent(event);

        QPen gridPen(Qt::SolidLine);
        gridPen.setColor(Qt::black);//(QColor(226, 226, 226));
        gridPen.setWidth(0);

        QPainter painter(viewport());

        painter.setPen(gridPen);
        for(int i = 0; i < 7; ++i) {
            int x = columnViewportPosition(i) + columnWidth(i) - 1;
            painter.drawLine(x, 0, x, viewport()->height());
        }

        for(int i = 0; i < 24; ++i) {
            int y = rowViewportPosition(i) + GRID_HEIGHT - 1;
            painter.drawLine(0, y, viewport()->width(), y);
        }

        painter.setPen(QPen(Qt::red, 1));

        int lineY = scan_line_pos_ - verticalScrollBar()->value();
        int pointX = visualRect(model()->index(0, todays_num_of_weeks_)).left();

        drawLine(painter, lineY);
        drawDot(painter, lineY, pointX);
        drawCurrentTime(painter, lineY, pointX);

        return ret;
    }

    void WeekTableWidget::updateScanLinePosition() {
        ++scan_line_pos_; // += 1 duo to the ViewportHeight is 60 * 24
        if (scan_line_pos_ > ViewportHeight) {
            scan_line_pos_ = 0;
            ++todays_num_of_weeks_;
        }

        int lineY = scan_line_pos_ - verticalScrollBar()->value();
        int minY = lineY - DOT_RADIUS - 2;
        int maxY = lineY + DOT_RADIUS + 1;

        if (maxY < 0 || minY > ViewportHeight)
            return;

        viewport()->update(0, minY, ViewportHeight, maxY - minY);
    }

    inline void WeekTableWidget::drawLine(QPainter &painter, int pointY) const {
        painter.drawLine(0, pointY, viewport()->width(), pointY);
    }

    inline void WeekTableWidget::drawDot(QPainter &painter, int pointY, int pointX) {
        painter.setPen(Qt::white);
        painter.setBrush(Qt::red);
        painter.drawEllipse(pointX - DOT_RADIUS - 1, pointY - DOT_RADIUS, 2 * DOT_RADIUS, 2 * DOT_RADIUS);
    }

    inline void WeekTableWidget::drawCurrentTime(QPainter &painter, int pointY, int pointX) {
        painter.setFont(QFont(painter.font().family(), TIME_DISPLAY_FONT_SIZE));
        QString currentTime = QTime::currentTime().toString("hh:mm");
        painter.setPen(QColor(188, 188, 188));
        painter.drawText(pointX + DOT_RADIUS, pointY + TIME_DISPLAY_Y_OFFSET, currentTime);
    }
} // touka
