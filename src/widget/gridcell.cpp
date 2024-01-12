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
#include <QtWidgets/QMenu>

#include "ui_GridCell.h"
#include "controller/AppManager.h"
#include "view/eventview.h"

namespace touka {
GridCell::GridCell(QWidget *parent)
    : QFrame(parent), ui(new Ui::GridCell), is_activate_(false) {
  ui->setupUi(this);
  applyTextColor(COMMON_CELL_TEXT_COLOR);
  ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(ui->listWidget, &QListWidget::customContextMenuRequested,
          [this](const QPoint &pos) {
            const auto menu = new QMenu(ui->listWidget);
            const auto actionNewEvt = new QAction(tr("New event"), menu);
            const auto actionDelEvt = new QAction(tr("Remove event"), menu);
            connect(actionNewEvt, &QAction::triggered, this, &GridCell::onActionNewEvt);
            connect(actionDelEvt, &QAction::triggered, this, &GridCell::onActionDelete);
            menu->addAction(actionNewEvt);
            // 只有当item不为空时才添加右键菜单
            if (!ui->listWidget->selectedItems().empty()) {
              menu->addAction(actionDelEvt);
            }
            menu->popup(ui->listWidget->mapToGlobal(pos));
          });

  // connect(&AppManager::instance(), &AppManager::eventAdded, this, [&](const EventPtr &evt) {
  //   if (!evt) return;
  //   const auto date = evt->get_dt_start().date();
  //   if (date != date_) return;
  //   ui->listWidget->addEvent(evt);
  // });
  connect(&AppManager::instance(), &AppManager::eventModified, this, [&](const EventPtr &evt, const EventPtr &_) {
    if (!evt) return;
    const auto date = evt->get_dt_start().date();
    if (date != date_) return;
    const auto evts = AppManager::instance().getEventsOfDay(date);
    ui->listWidget->setEvents(evts);
  });

  // ui->listWidget->setFrameStyle(NoFrame);
  // ui->listWidget->setStyleSheet();
}

GridCell::GridCell(const Date &date, QWidget *parent) : GridCell(parent) {
  setDate(date);
}

GridCell::~GridCell() { delete ui; }

void GridCell::setDate(const Date &date) {
  date_ = date;
  const auto evts = AppManager::instance().getEventsOfDay(date);
  ui->listWidget->setEvents(evts);
  refresh();
}

bool GridCell::isActivate() const { return is_activate_; }

inline void GridCell::setDayOfMonthText(bool showMonthStr) const {
  auto showStr = date_.toString("d");
  if (showMonthStr) {
    QString monthStr;
    const auto month = static_cast<Month>(date_.month());
    if (QLocale::system().name().mid(0, 2) == "en")
      monthStr = DateUtil::getLiteralMonth(month).mid(0, 3) + ' ';
    showStr.prepend(monthStr);
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
      "	background-position: center right;"
      " color: rgb(255, 255, 255);"
      "}");
}

void GridCell::refresh() {
  if (isWeekend())
    setWeekendStyles();
  if (date_ == Date::currentDate()) {
    setDayOfMonthText();
    setCurrentDayStyles();
  } else {
    setDayOfMonthText(date_.day() == 1);
    ui->lbDate->setStyleSheet("");
  }
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

// void GridCell::mouseReleaseEvent(QMouseEvent *event) {
//   if (event->button() == Qt::LeftButton)
//     onActionNewEvt();
//   QFrame::mouseReleaseEvent(event);
// }

void GridCell::contextMenuEvent(QContextMenuEvent* event) {
  QFrame::contextMenuEvent(event);
}

void GridCell::updateEvent(const Event &evt) {}

void GridCell::selectOut() const {
  ui->listWidget->clearSelection();
}

void GridCell::onActionNewEvt() const {
  const auto evt = AppManager::createEmptyEvt(QDateTime(date_, QTime::currentTime()));
  if (!evt) return;
  // ui->listWidget->addEvent(evt);
  EventView::eventEditMenu(evt, QCursor::pos(), ui->listWidget);
}

void GridCell::onActionDelete() const {
  auto items = ui->listWidget->selectedItems();
  if (items.empty()) return;
  auto id = ui->listWidget->removeEvt(ui->listWidget->row(items[0]));
  AppManager::instance().deleteEvent(id.toStdString().c_str());
}

void GridCell::setItemSelectable(const bool isSelectable) const {
  if (isSelectable)
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  else {
    ui->listWidget->clearSelection();
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
  }
}

void GridCell::applyTextColor(const QColor &color) const {
  QPalette pal(ui->lbDate->palette());
  pal.setColor(QPalette::Text, color);
  ui->lbDate->setPalette(pal);
}

} // namespace touka
