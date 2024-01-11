//
// Created by Touka on 2023/12/17.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_EventView.h" resolved

#include "eventview.h"

#include <QDataWidgetMapper>
#include <QAbstractItemView>
#include <qpainter.h>

#include <QtCore/qparallelanimationgroup.h>
#include <QtCore/qpropertyanimation.h>

#include "controller/AppManager.h"
#include "ui_EventView.h"

namespace touka {
EventView::EventView(QWidget *parent)
    : QWidget(parent), ui(new Ui::EventView), is_windows_(false) {
  ui->setupUi(this);

  init();
  QPalette pal(this->palette());
  pal.setColor(QPalette::Window, BACKGROUND_COLOR);
  setAutoFillBackground(true);
  setPalette(pal);
}

EventView::EventView(EventPtr evt, QWidget *parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint),
      ui(new Ui::EventView), is_windows_(true), data_widget_mapper_(std::make_unique<QDataWidgetMapper>(this)), event_(std::move(evt)) {
  ui->setupUi(this);

  init();
  setAttribute(Qt::WA_TranslucentBackground);
  setAttribute(Qt::WA_DeleteOnClose);
  int left, top, right, bottom;
  layout()->getContentsMargins(&left, &top, &right, &bottom);
  // set the layout left margin to TRIANGLE_HEIGHT
  layout()->setContentsMargins(TRIANGLE_HEIGHT, top, right, bottom);
  // register event filter
  // qApp->installEventFilter(this);

  // if (!evt) return;
  // data_widget_mapper_->setSubmitPolicy(QDataWidgetMapper::SubmitPolicy::AutoSubmit);
  // data_widget_mapper_->setModel(evt.get());
  // data_widget_mapper_->addMapping(ui->leSummary, Event::Columns::SummaryColumn);
  // // data_widget_mapper_->addMapping(ui->cbCategory, Event::Columns::CategoriesColumn);
  // data_widget_mapper_->addMapping(ui->leAddLocation, Event::Columns::LocationColumn);
  // data_widget_mapper_->addMapping(ui->cbAllDay, Event::Columns::AllDayColumn);
  // data_widget_mapper_->addMapping(ui->dteStarts, Event::Columns::StartTimeColumn);
  // data_widget_mapper_->addMapping(ui->dteEnds, Event::Columns::EndTimeColumn);
  // data_widget_mapper_->addMapping(ui->cbPrivate, Event::Columns::PrivateColumn);
  // data_widget_mapper_->addMapping(ui->teNote, Event::Columns::DescriptionColumn);
  // data_widget_mapper_->toFirst();

  // TODO this is temp code, need to be removed
  ui->cbRepeat->setHidden(true);
  ui->cbEndRepeat->setHidden(true);
  ui->cbTravelTime->setHidden(true);
  ui->cbShowAs->setHidden(true);
  ui->label_3->setHidden(true);
  ui->label_4->setHidden(true);
  ui->label_5->setHidden(true);
  ui->label_7->setHidden(true);
}

void EventView::init() const {
  const auto categories = AppManager::getEvtCategories();
  for (const auto &category : categories) {
    ui->cbCategory->addCategory(*category);
  }
  if (!event_) return;
  ui->leSummary->setText(event_->get_summary());
  ui->cbCategory->setCurrentText(event_->get_categories()->get_cate_name());
  ui->leAddLocation->setText(event_->get_location());
  ui->cbAllDay->setChecked(event_->is_all_day());
  ui->dteStarts->setDateTime(event_->get_dt_start());
  ui->dteEnds->setDateTime(event_->get_dt_end());
  ui->cbPrivate->setChecked(event_->is_private());
  ui->teNote->setText(event_->get_description());
  // ui->cbAlert->setEditable(true);
  // ui->cbAlert->setInsertPolicy(QComboBox::NoInsert);
  if (const auto alert = event_->get_alarm_time(); alert.has_value()) {
    ui->cbAlert->setEditText(alert.value().toString("yyyy-MM-dd hh:mm"));
    qDebug() << alert.value().toString("yyyy-MM-dd hh:mm");
  }
}

auto EventView::playAnimationGroup(QObject *target, const QRect &startGeometry,
                                   const QRect &endGeometry, int duration,
                                   qreal startOpacity, qreal endOpacity)
    -> QParallelAnimationGroup * {
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
  if (event_) {
    event_->set_summary(ui->leSummary->text());
    event_->set_categories(AppManager::getEvtCategoryByName(ui->cbCategory->currentText()));
    event_->set_location(ui->leAddLocation->text());
    event_->set_all_day(ui->cbAllDay->isChecked());
    event_->set_dt_start(ui->dteStarts->dateTime());
    event_->set_dt_end(ui->dteEnds->dateTime());
    event_->set_private(ui->cbPrivate->isChecked());
    event_->set_description(ui->teNote->toPlainText());
    switch (ui->cbAlert->currentIndex()) {
    case 0:
      event_->set_alarm_time(std::nullopt);
      break;
    case 1:
      event_->set_alarm_time(event_->get_dt_start());
      break;
    case 2:
      event_->set_alarm_time(event_->get_dt_start().addSecs(-60 * 5));
      break;
    case 3:
      event_->set_alarm_time(event_->get_dt_start().addSecs(-60 * 10));
      break;
    case 4:
      event_->set_alarm_time(event_->get_dt_start().addSecs(-60 * 15));
      break;
    case 5:
      event_->set_alarm_time(event_->get_dt_start().addSecs(-60 * 30));
      break;
    case 6:
      event_->set_alarm_time(event_->get_dt_start().addSecs(-1 * 60 * 60));
      break;
    case 7:
      event_->set_alarm_time(event_->get_dt_start().addSecs(-2 * 60 * 60));
      break;
    case 8:
      event_->set_alarm_time(event_->get_dt_start().addDays(-1));
      break;
    case 9:
      event_->set_alarm_time(event_->get_dt_start().addDays(-2));
      break;
    default:
      event_->set_alarm_time(std::nullopt);
      break;
    }
    AppManager::instance().modifyEvent(event_, event_);
  }
  // data_widget_mapper_->submit();
  // auto id = data_widget_mapper_->model()->data(data_widget_mapper_->model()->index(0, Event::Columns::IdColumn)).toString();
  // AppManager::instance().modifyEvent(evt, evt);
  delete ui;
}

void EventView::eventEditMenu(const EventPtr& evt, QPoint pos, QWidget* parent) {
  const auto eventView = new EventView(evt, parent);

  pos.rx() += 10;
  pos.ry() = pos.y() - eventView->height() / 2;
  eventView->move(pos);
  eventView->show();

  const auto group = playAnimationGroup(eventView,
      QRect(pos.x() + 10, pos.y() + eventView->geometry().height() / 2, 1, 10),
      eventView->geometry(), 500, 0, 1);

  connect(group, &QParallelAnimationGroup::finished, eventView,
          [eventView]() { eventView->setFixedSize(eventView->size()); });
}

void EventView::eventEditMenu(const String &evtId, QPoint pos, QWidget* parent) {
  const auto evt = AppManager::instance().getEventById(evtId);
  eventEditMenu(evt, pos, parent);
}

//
// bool EventView::eventFilter(QObject *watched, QEvent *event) {
//   // This lambda function takes a rect parameter representing the geometry of
//   // the window.
//   const auto minimizeAndClose = [this](const QRect &rect) {
//     // Set the minimum size of the window to 0, 0 because of a fixed size was
//     // set before.
//     setMinimumSize(0, 0);
//
//     const auto group = playAnimationGroup(
//         this, rect, QRect(rect.x(), rect.y() + rect.height() / 2, 0, 0), 150, 1,
//         0);
//
//     connect(group, &QPropertyAnimation::finished, this, &EventView::close);
//   };
//
//   // If the event is the application losing focus or a mouse button press in the
//   // non-client area, close the window. This is to close the window when the
//   // user switches to another application or clicks on the title bar of the
//   // window.
// //   if (event->type() == QEvent::ApplicationDeactivate ||
// //       event->type() == QEvent::NonClientAreaMouseButtonPress) {
// //     minimizeAndClose(this->geometry());
// //     return true;
// //   }
//
//   // If the event is a mouse button press, check if the mouse is inside the
//   // window. If the mouse is not press on this EventView widget, close the
//   // window.
//   if (event->type() == QEvent::MouseButtonPress) {
//     qDebug() << "mouse press";
//     auto region = visibleRegion();
//     if (!region.contains(mapFromGlobal(QCursor::pos()))) {
//       auto focusWidget = QApplication::focusWidget();
//       // Check if the focus widget is a child of the current window.
//     //   if (!dropdown_views_.contains(
//     //           qobject_cast<QAbstractItemView *>(focusWidget))) {
//     //     minimizeAndClose(this->geometry());
//     //     return true;
//     //   }
//
//       //   // Check if the focus is on any QComboBox's dropdown list.
//       //   bool focusOnDropdownList = false;
//       //   for (QComboBox *comboBox : comboBoxes) {
//       //     if (view && view == comboBox->view()) {
//       //       focusOnDropdownList = true;
//       //       break;
//       //     }
//       //   }
//       //   if (!focusOnDropdownList) {
//       //     minimizeAndClose(this->geometry());
//       //     return true;
//       //   }
//     }
//   }
//
//   // If the event is not one of the above, pass it to the base class.
//   return QWidget::eventFilter(watched, event);
// }

void EventView::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  if (!is_windows_)
    return;

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

} // namespace touka
