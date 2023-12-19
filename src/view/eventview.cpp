//
// Created by Touka on 2023/12/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_EventView.h" resolved

#include "eventview.h"

#include <QPainter.h>

#include <QtCore/qparallelanimationgroup.h>
#include <QtCore/qpropertyanimation.h>

#include "ui_EventView.h"
#include "controller/EventManager.h"
#include "entity/EventCategories.h"

namespace touka {
    EventView::EventView( QWidget *parent) :
        QWidget(parent), ui(new Ui::EventView), is_windows_(false) {
        ui->setupUi(this);

        init();
        QPalette pal(this->palette());
        pal.setColor(QPalette::Window, BACKGROUND_COLOR);
        setAutoFillBackground(true);
        setPalette(pal);
    }


    EventView::EventView(Event *evt, QWidget* parent) :
        QWidget(parent, Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint), ui(new Ui::EventView), is_windows_(true) {
        ui->setupUi(this);

        init();
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_DeleteOnClose);
        int left, top, right, bottom;
        layout()->getContentsMargins(&left, &top, &right, &bottom);
        // set the layout left margin to TRIANGLE_HEIGHT
        layout()->setContentsMargins(TRIANGLE_HEIGHT, top, right, bottom);
        //register event filter
        qApp->installEventFilter(this);
    }

    void EventView::init() {
        auto categories = EventManager::getEvtCategories();
        for (const auto & category : categories) {
            ui->cbCategory->addCategory(category);
        }
    }

    auto EventView::playAnimationGroup(QObject* target, const QRect& startGeometry, const QRect& endGeometry,
        int duration, qreal startOpacity, qreal endOpacity) -> QParallelAnimationGroup* {
        const auto fadeAnimation = new QPropertyAnimation(target, "windowOpacity");
        fadeAnimation->setDuration(duration);
        fadeAnimation->setStartValue(startOpacity);
        fadeAnimation->setEndValue(endOpacity);

        const auto shrinkAnimation = new QPropertyAnimation(target, "geometry");
        shrinkAnimation->setDuration(duration);
        shrinkAnimation->setStartValue(startGeometry);
        shrinkAnimation->setEndValue(endGeometry);
        if (duration >= 500)
            shrinkAnimation->setEasingCurve(QEasingCurve::InOutBack);

        const auto group = new QParallelAnimationGroup(target);
        group->addAnimation(fadeAnimation);
        group->addAnimation(shrinkAnimation);
        group->start(QAbstractAnimation::DeleteWhenStopped);
        return group;
    }

    EventView::~EventView() {
        delete ui;
    }

    void EventView::menu(QPoint pos, QWidget *parent) {
        // Todo get it done
        const auto eventView = new EventView(nullptr, parent);
        pos.rx() += 10;
        pos.ry() = pos.y() - eventView->height() / 2;
        eventView->move(pos);
        eventView->show();

        const auto group =
            playAnimationGroup(eventView,
            QRect(pos.x() + 10, pos.y() + eventView->geometry().height() / 2, 1, 10),
            eventView->geometry(), 500, 0, 1);

        connect(group, &QParallelAnimationGroup::finished, eventView, [eventView]() {
            eventView->setFixedSize(eventView->size());
        });
    }

    bool EventView::eventFilter(QObject* watched, QEvent* event) {
        // This lambda function takes a rect parameter representing the geometry of the window.
        const auto minimizeAndClose = [this](const QRect &rect) {
            // Set the minimum size of the window to 0, 0 because of a fixed size was set before.
            setMinimumSize(0, 0);

            const auto group =
                playAnimationGroup(this,
                rect,
                QRect(rect.x(), rect.y() + rect.height() / 2, 0, 0),
                150, 1, 0);

            connect(group, &QPropertyAnimation::finished, this, &EventView::close);
        };

        // If the event is the application losing focus or a mouse button press in the non-client area, close the window.
        // This is to close the window when the user switches to another application or clicks on the title bar of the window.
        if (event->type() == QEvent::ApplicationDeactivate ||
            event->type() == QEvent::NonClientAreaMouseButtonPress) {
            minimizeAndClose(this->geometry());
            return true;
        }

        // If the event is a mouse button press, check if the mouse is inside the window.
        // If the mouse is not press on this EventView widget, close the window.
        if (event->type() == QEvent::MouseButtonPress) {
            auto rect = this->rect();
            rect.setX(rect.x() + TRIANGLE_HEIGHT); // The triangle is not part of the window.
            if (!rect.contains(mapFromGlobal(QCursor::pos()))) {
                minimizeAndClose(this->geometry());
                return true;
            }
        }

        // If the event is not one of the above, pass it to the base class.
        return QWidget::eventFilter(watched, event);
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

} // touka
