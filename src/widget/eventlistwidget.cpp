//
// Created by Touka on 2024/1/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_EventListWidget.h" resolved

#include "eventlistwidget.h"

#include <QtGui/qevent.h>
#include <QtWidgets/QMenu>
#include <QtWidgets/QLabel>

#include "eventlistitem.h"
#include "controller/AppManager.h"
#include "view/eventview.h"

namespace touka {
EventListWidget::EventListWidget(QWidget *parent) :
    QListWidget(parent) {
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setGridSize(QSize(0, LABEL_HEIGHT));
    setMinimumHeight(LABEL_HEIGHT * 2 + 2);
}

EventListWidget::~EventListWidget()=default;

void EventListWidget::addEvent(const EventPtr& evt) {
    if (!evt) return;
    auto label = new EventListItem(this);
    label->setName(evt->get_summary());
    if (!evt->is_all_day())
        label->setTime(evt->get_dt_start().time());
    label->set_evt_id(evt->get_uid());
    auto color = QColor(0, 0, 0);
    if (evt->get_categories())
        color = evt->get_categories()->get_cate_color();
    color.setAlpha(128);
    // label->setBackgroudColor(color);
    label->setStyleSheet(R"(
        EventListItem {
	        border-left: 3px solid black;
            border-radius: 4px;
        }
        )");

    labels_.push_back(label);
    refresh();
}

void EventListWidget::addEvents(const EventPtrList& evts) {
    for (const auto & evt : evts) {
        if (!evt) continue;
        auto label = new EventListItem(this);
        label->setName(evt->get_summary());
        label->set_evt_id(evt->get_uid());
        if (!evt->is_all_day())
            label->setTime(evt->get_dt_start().time());
        auto color = QColor(163, 163, 163);
        if (evt->get_categories())
            color = evt->get_categories()->get_cate_color();
        color.setAlpha(128);
        label->setBackgroudColor(color);
        // label->setStyleSheet(R"(
        // QWidget {
        //     border-radius: 4px;
        // }
        // )");
        labels_.push_back(label);
    }
    refresh();
}

void EventListWidget::refresh() {
    clearSelection();
    clear();
    const auto size = labels_.size();
    if (size == 0) return;
    for (int i = 0; i < size; ++i) {
        const auto item = new QListWidgetItem(this);
        setItemWidget(item, labels_[i]);
        item->setSizeHint(QSize(0, LABEL_HEIGHT));
        addItem(item);
    }

    label_more_ = new QLabel(this);
    label_more_->setStyleSheet("padding-left: 4px; background-color: transparent;");
    auto font = label_more_->font();
    font.setPointSize(10);
    label_more_->setFont(font);

    auto pal = label_more_->palette();
    pal.setColor(QPalette::Text, QColor(126, 126, 126));
    label_more_->setPalette(pal);

    const auto more_item = new QListWidgetItem(this);
    more_item->setFlags(Qt::ItemIsEnabled);
    more_item->setSizeHint(QSize(0, 10));
    setItemWidget(more_item, label_more_);
    addItem(more_item);
    update();
}

void EventListWidget::clearEvent() {
    clear();
    labels_.clear();
    update();
}

void EventListWidget::setEvents(const EventPtrList& evts) {
    clear();
    labels_.clear();
    addEvents(evts);
}

QString EventListWidget::removeEvt(const int idx) {
    if (idx < 0 || idx >= labels_.size()) return "";
    auto uid = labels_[idx]->get_evt_id();
    labels_.erase(labels_.begin() + idx);
    takeItem(idx);
    update();
    return uid;
}

void EventListWidget::mousePressEvent(QMouseEvent* event) {
    const auto item = itemAt(event->pos());
    if (!item) return;
    if (event->button() == Qt::LeftButton) {
        if (item->isSelected()) {
            const auto uid = labels_[row(item)]->get_evt_id();
            EventView::eventEditMenu(uid, QCursor::pos(), this);
        }
    }
    item->setSelected(true);

    QListWidget::mousePressEvent(event);
}

void EventListWidget::update() const {
    auto visibleCount = viewport()->height() / LABEL_HEIGHT;
    const auto count = this->count();
    if (count == 0) return;
    if (visibleCount >= count) {
        for (int i = 0; i < count; ++i) {
            item(i)->setHidden(false);
        }
        item(count - 1)->setHidden(true);
        return;
    }

    visibleCount -= 1;
    item(count - 1)->setHidden(visibleCount >= count - 1);

    for (int i = 0; i < visibleCount; ++i) {
        label_more_->setText(QString::number(count - visibleCount - 1) + " more...");
        item(i)->setHidden(false);
    }
    for (int i = visibleCount; i < count - 1; ++i) {
        item(i)->setHidden(true);
    }
}

void EventListWidget::mouseDoubleClickEvent(QMouseEvent* event) {
    if (const auto item = itemAt(event->pos())) {
        // if (item->isSelected())
        //     EventView::menu(QCursor::pos(), this);
    } else {

    }
    QListWidget::mouseDoubleClickEvent(event);
}

// void EventListWidget::contextMenuEvent(QContextMenuEvent* context_menu_event) {
//     if (!itemAt(context_menu_event->pos())) return;
//     QMenu menu(this);
//     menu.addAction(tr("Edit"));
//     menu.addAction(tr("Delete"));
//     menu.show();
// }

void EventListWidget::resizeEvent(QResizeEvent* e) {
    update();
    QListWidget::resizeEvent(e);
}
} // touka
