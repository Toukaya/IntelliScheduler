//
// Created by Touka on 2023/12/17.
//

#ifndef EVENTVIEW_H
#define EVENTVIEW_H

#include <QWidget>

#include "types.hpp"

namespace touka {
class Event;
}

class QParallelAnimationGroup;
class QAbstractItemView;

namespace touka {
QT_BEGIN_NAMESPACE

namespace Ui {
class EventView;
}

QT_END_NAMESPACE

constexpr static int8 TRIANGLE_HEIGHT = 12;
constexpr static int8 TRIANGLE_HALF_WEIGHT = 12;
constexpr static Color BACKGROUND_COLOR = QColor(240, 240, 240);

class EventView : public QWidget {
  Q_OBJECT

public:
  explicit EventView(QWidget *parent = nullptr);

  ~EventView() override;

public slots:
  static void menu(/*TODO Event infomation param*/ QPoint pos, QWidget *parent);

  bool eventFilter(QObject *watched, QEvent *event) override;

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  void init();

  explicit EventView(Event *evt, QWidget *parent = nullptr);

  Ui::EventView *ui;

  bool is_windows_;

  QSet<QAbstractItemView *> dropdown_views_;

  static auto playAnimationGroup(QObject *target, const QRect &startGeometry,
                                 const QRect &endGeometry, int duration,
                                 qreal startOpacity, qreal endOpacity)
      -> QParallelAnimationGroup *;
};
} // namespace touka

#endif // EVENTVIEW_H
