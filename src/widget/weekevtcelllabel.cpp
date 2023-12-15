//
// Created by Touka on 2023/12/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WeekEvtCellLabel.h" resolved

#include "weekevtcelllabel.h"

#include <QPainter.h>
#include <QtGui/qevent.h>

#include "ui_WeekEvtCellLabel.h"

namespace touka {
    WeekEvtCellLabel::WeekEvtCellLabel(QWidget *parent) :
            QFrame(parent), ui(new Ui::WeekEvtCellLabel) {
        ui->setupUi(this);
        setAutoFillBackground(true);
        // setStyleSheet("touka::WeekEvtCellLabel {border-radius: 10px;}");
    }

    WeekEvtCellLabel::~WeekEvtCellLabel() {
        delete ui;
    }

    void WeekEvtCellLabel::setTime(const QTime& time) const {
        ui->lbTime->setText(time.toString("hh:mm"));
    }

    void WeekEvtCellLabel::setContext(const QString& context) const {
        ui->lbEvtInfo->setText(context);
    }

    void WeekEvtCellLabel::setColor(const QColor& color) {
        background_color_ = color;
        setStyleSheet(QString("color: %1").arg(color.name()));
    }

    void WeekEvtCellLabel::paintEvent(QPaintEvent* paint_event) {
        QPainter painter(this);

        background_color_.setAlpha(255);
        painter.fillRect(0, 0, 3, height(), background_color_);
        background_color_.setAlpha(36);
        painter.fillRect(3, 0, width()-3, height(), background_color_);

        QFrame::paintEvent(paint_event);
    }

    void WeekEvtCellLabel::resizeEvent(QResizeEvent* event) {
        if (event->size().height() < 32)
            ui->lbTime->hide();
        else
            ui->lbTime->show();

        QFrame::resizeEvent(event);
    }
} // touka
