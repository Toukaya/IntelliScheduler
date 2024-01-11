//
// Created by Touka on 2024/1/9.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_EventListItem.h" resolved

#include "eventlistitem.h"

#include <QTime>

#include "ui_EventListItem.h"

namespace touka {
EventListItem::EventListItem(QWidget *parent)
    : QWidget(parent), ui(new Ui::EventListItem) {
  ui->setupUi(this);
  ui->lbEvtTime->clear();
}

EventListItem::~EventListItem() { delete ui; }

const QString &EventListItem::get_name() const { return name_; }

const QTime &EventListItem::get_time() const { return time_; }

const QString &EventListItem::get_evt_id() const { return evt_id_; }

void EventListItem::set_evt_id(const QString &evt_id) { evt_id_ = evt_id; }

void EventListItem::setName(const QString &name) {
  name_ = name;
  ui->lbEvtName->setText(name);
}

void EventListItem::setTime(const QTime &time) {
  time_ = time;
  ui->lbEvtTime->setText(time.toString("hh:mm"));
}

void EventListItem::setBackgroudColor(const QColor &color) {
  auto pal = palette();
  pal.setColor(QPalette::Base, color);
  setAutoFillBackground(true);
  setPalette(pal);
}
} // namespace touka
