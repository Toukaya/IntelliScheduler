//
// Created by Touka on 2023/12/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WeekTableWidget.h" resolved

#include "weektablewidget.h"
#include "ui_WeekTableWidget.h"
#include <QTimer>
#include <QPainter>
#include <QScrollBar>


namespace touka {
    WeekTableWidget::WeekTableWidget(QWidget *parent) :
            QTableWidget(parent), ui(new Ui::WeekTableWidget), scan_line_pos_(0) {
        ui->setupUi(this);

        // TODO remove this temp code
        auto timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [&] {
            if (scan_line_pos_ > viewport()->height()) return ;
            // update line position here
            ++scan_line_pos_;

            viewport()->update();  // Trigger paint event for viewport
        });
        timer->start(1000);  // Move the line every 1 second
    }

    WeekTableWidget::~WeekTableWidget() {
        delete ui;
    }

    void WeekTableWidget::paintEvent(QPaintEvent *e) {
        QTableView::paintEvent(e);

        QPainter painter(viewport());
        painter.setPen(QPen(Qt::red, 1));
        int offset = verticalScrollBar()->value();
        painter.drawLine(0, scan_line_pos_ - offset, viewport()->width(), scan_line_pos_ - offset);
    }
} // touka
