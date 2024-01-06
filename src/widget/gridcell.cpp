//
// Created by Touka on 2023/12/8.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_GridCell.h" resolved

#include "gridcell.h"
#include "utils/DateUtil.h"
#include <QtCore/qdatetime.h>
#include <QtGui/qevent.h>
#include <qpainter.h>

#include "ui_GridCell.h"
#include "view/eventview.h"

namespace touka {
GridCell::GridCell(QWidget *parent)
    : QFrame(parent), ui(new Ui::GridCell), is_activate_(false) {
  ui->setupUi(this);
  applyTextColor(COMMON_CELL_TEXT_COLOR);
}

GridCell::GridCell(const Date &date, QWidget *parent) : GridCell(parent) {
  setDate(date);
}

GridCell::~GridCell() { delete ui; }

void GridCell::setDate(const Date &date) {
  date_ = date;
  refresh();
}

bool GridCell::isActivate() const { return is_activate_; }

inline void GridCell::setDayOfMonthText() const {
  auto showStr = date_.toString("d");
  if (date_.day() == 1) {
    const auto month = static_cast<Month>(date_.month());
    if (QLocale::system().name().mid(0, 2) == "en")
      ui->lbMonth->setText(DateUtil::getLiteralMonth(month).mid(0, 3) + ' ');
  } else {
    ui->lbMonth->clear();
  }

  ui->lbDate->setText(showStr);
}

inline void GridCell::setWeekendStyles() {
  QPalette pal(this->palette());
  pal.setColor(QPalette::Base, WEEKEND_BACKGROUND_COLOR);
  this->setAutoFillBackground(true);
  this->setPalette(pal);
  applyTextColor(WEEKEND_CELL_TEXT_COLOR);
}

inline void GridCell::setCurrentDayStyles() const {
  ui->lbDate->setStyleSheet(
      "QLabel {"
      "	background-image: url(:/icon/resource/icon/circle.svg);"
      "	background-repeat: none;"
      "	background-position: center center;"
      " color: rgb(255, 255, 255);"
      "}");
}

void GridCell::refresh() {
  setDayOfMonthText();
  if (isWeekend())
    setWeekendStyles();
  if (date_ == Date::currentDate())
    setCurrentDayStyles();
  else
    ui->lbDate->setStyleSheet("");
}

void GridCell::setActivate(const bool isActivate) {
  is_activate_ = isActivate;

  QPalette pal(ui->lbDate->palette());
  if (!isActivate)
    pal.setColor(QPalette::Text, NOT_ACTIVATED_CELL_TEXT_COLOR);
  else if (!isWeekend())
    pal.setColor(QPalette::Text, COMMON_CELL_TEXT_COLOR);
  ui->lbDate->setPalette(pal);
}

bool GridCell::isWeekend() const {
  const int dayOfWeek = date_.dayOfWeek();
  return dayOfWeek == Qt::Saturday || dayOfWeek == Qt::Sunday;
}

void GridCell::mouseReleaseEvent(QMouseEvent *event) {
  // 判断用户按下的是哪一个鼠标键
  if (event->button() == Qt::RightButton)
    EventView::menu(QCursor::pos(), this);
  QFrame::mouseReleaseEvent(event);
}

void GridCell::updateEvent(const Event &evt) {}

void GridCell::applyTextColor(const QColor &color) const {
  QPalette pal(ui->lbDate->palette());
  pal.setColor(QPalette::Text, color);
  ui->lbDate->setPalette(pal);
}

} // namespace touka
