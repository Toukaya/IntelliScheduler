//
// Created by Touka on 2024/1/9.
//

#ifndef EVENTLISTITEM_H
#define EVENTLISTITEM_H

#include <QTime>
#include <QWidget>

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui {
class EventListItem;
}
QT_END_NAMESPACE

class EventListItem : public QWidget {
  Q_OBJECT

public:
  explicit EventListItem(QWidget *parent = nullptr);
  ~EventListItem() override;

  [[nodiscard]] const QString &get_name() const;

  [[nodiscard]] const QTime &get_time() const;

  [[nodiscard]] const QString &get_evt_id() const;

public slots:

  void setName(const QString &name);

  void setTime(const QTime &time);

  void setBackgroudColor(const QColor &color);

  void set_evt_id(const QString &evt_id);

private:
  Ui::EventListItem *ui;

  QString name_;

  QTime time_;

  QString evt_id_;
};
} // namespace touka

#endif // EVENTLISTITEM_H
