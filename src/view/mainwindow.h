//
// Created by Touka on 2023/12/4.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MonthView;
class WeekView;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

private:
  void pushWidget2StackView(QWidget *widget) const;

public slots:

  void goMonthView();

protected:
  void closeEvent(QCloseEvent *event) override;

private slots:
  void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
  Ui::MainWindow *ui;

  std::unique_ptr<MonthView> month_view_;
  std::unique_ptr<WeekView> week_view_;
};
} // namespace touka

#endif // MAINWINDOW_H
