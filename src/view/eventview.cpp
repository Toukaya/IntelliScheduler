//
// Created by Touka on 2023/12/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_EventView.h" resolved

#include "eventview.h"

#include <QPainter.h>

#include <QtCore/qparallelanimationgroup.h>
#include <QtCore/qpropertyanimation.h>

#include "ui_EventView.h"

namespace touka {
    EventView::EventView(bool isWindow, QWidget *parent) :
        QWidget(parent, Qt::Window), ui(new Ui::EventView), is_windows_(isWindow) {
        ui->setupUi(this);

        if (is_windows_) {
            setWindowFlags(Qt::FramelessWindowHint);
            setAttribute(Qt::WA_TranslucentBackground);
            setAttribute(Qt::WA_DeleteOnClose);
            int left, top, right, bottom;
            layout()->getContentsMargins(&left, &top, &right, &bottom);
            // set the layout left margin to TRIANGLE_HEIGHT
            layout()->setContentsMargins(TRIANGLE_HEIGHT, top, right, bottom);
            // setFocus();
        } else {
            QPalette pal(this->palette());
            pal.setColor(QPalette::Window, BACKGROUND_COLOR);
            setAutoFillBackground(true);
            setPalette(pal);
        }
    }


    EventView::EventView(QWidget* parent) :
        QWidget(parent, Qt::Window), ui(new Ui::EventView), is_windows_(true) {
        ui->setupUi(this);

        // setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_DeleteOnClose);
        int left, top, right, bottom;
        layout()->getContentsMargins(&left, &top, &right, &bottom);
        // set the layout left margin to TRIANGLE_HEIGHT
        layout()->setContentsMargins(TRIANGLE_HEIGHT, top, right, bottom);
        // setFocus();
    }

    EventView::~EventView() {
        delete ui;
    }

    void EventView::menu(QPoint pos, QWidget *parent) {
        // Todo implement it
        const auto eventView = new EventView(parent);
        pos.ry() = pos.y() - eventView->height() / 2;
        eventView->move(pos);
        eventView->show();

        const auto fadeAnimation = new QPropertyAnimation(eventView, "windowOpacity");
        fadeAnimation->setDuration(650);
        fadeAnimation->setStartValue(0);
        fadeAnimation->setEndValue(1);

        const auto shrinkAnimation = new QPropertyAnimation(eventView, "geometry");
        shrinkAnimation->setDuration(650);
        shrinkAnimation->setStartValue(QRect(eventView->geometry().x(), eventView->geometry().y() + eventView->geometry().height() / 2, 0, 0));
        shrinkAnimation->setEndValue(eventView->geometry());
        shrinkAnimation->setEasingCurve(QEasingCurve::InOutBack);

        const auto group = new QParallelAnimationGroup;
        group->addAnimation(fadeAnimation);
        group->addAnimation(shrinkAnimation);
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }

    void EventView::paintEvent(QPaintEvent* event) {
        QWidget::paintEvent(event);
        if (!is_windows_) return;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(BACKGROUND_COLOR));
        painter.setPen(Qt::NoPen);
        auto rect = this->rect();
        rect.setX(rect.x() + TRIANGLE_HEIGHT);
        // Draw the background
        painter.drawRoundedRect(rect, 15, 15);

        QPolygon triangle;
        triangle << QPoint(0, height() / 2)
                 << QPoint(TRIANGLE_HEIGHT, height() / 2 - TRIANGLE_HALF_WEIGHT)
                 << QPoint(TRIANGLE_HEIGHT, height() / 2 + TRIANGLE_HALF_WEIGHT);

        // Draw the triangle
        painter.drawPolygon(triangle);
    }

    void EventView::focusOutEvent(QFocusEvent* event) {
        QWidget::focusOutEvent(event);

        if (!is_windows_) return;
        // TODO fix it
        QWidget *currFocus = QApplication::focusWidget();
        if (currFocus && !isAncestorOf(currFocus))
            return;

        const auto fadeAnimation = new QPropertyAnimation(this, "windowOpacity");
        fadeAnimation->setDuration(200);
        fadeAnimation->setStartValue(1);
        fadeAnimation->setEndValue(0);

        const auto shrinkAnimation = new QPropertyAnimation(this, "geometry");
        shrinkAnimation->setDuration(200);
        shrinkAnimation->setStartValue(this->geometry());
        shrinkAnimation->setEndValue(QRect(this->geometry().x(), this->geometry().y() + this->geometry().height() / 2, 0, 0));
        // shrinkAnimation->setEasingCurve(QEasingCurve::OutBack);

        const auto group = new QParallelAnimationGroup;
        group->addAnimation(fadeAnimation);
        group->addAnimation(shrinkAnimation);
        group->start(QAbstractAnimation::DeleteWhenStopped);

        connect(fadeAnimation, &QPropertyAnimation::finished, this, &EventView::close);
    }

} // touka
