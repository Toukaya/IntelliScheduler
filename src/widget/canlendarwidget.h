//
// Created by touka on 2023/12/4.
//

#ifndef CANLENDARWIDGET_H
#define CANLENDARWIDGET_H

#include <QCalendarWidget>

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui {
class CanlendarWidget;
}
QT_END_NAMESPACE

class CanlendarWidget : public QCalendarWidget {
  Q_OBJECT

public:
  explicit CanlendarWidget(QWidget *parent = nullptr);
  ~CanlendarWidget() override;

private:
  Ui::CanlendarWidget *ui;
};
} // namespace touka

#endif // CANLENDARWIDGET_H
