//
// Created by Touka on 2023/12/4.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_MainWindow.h" resolved

#include "mainwindow.h"

#include <QtGui/qevent.h>

#include "AppConfig.hpp"
#include "monthview.h"
#include "ui_MainWindow.h"
#include "weekview.h"

namespace touka {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // TODO: remove this test code
  month_view_ = std::make_unique<MonthView>();
  week_view_ = std::make_unique<WeekView>();
  pushWidget2StackView(month_view_.get());
  // TODO this is temp code, need to be removed
  ui->viewBtngroupFrame->setHidden(true);
  ui->btnQuickCreate->setHidden(true);

  QPalette pal(this->palette());
  pal.setColor(QPalette::Window, Qt::white);
  this->setAutoFillBackground(true);
  this->setPalette(pal);

  setWindowTitle(QString::fromStdString(std::string(AppConfig::appName())));

  // 创建系统托盘图标
  const auto trayIcon = AppConfig::getTrayIcon();
  trayIcon->setToolTip(
      QString::fromStdString(std::string(AppConfig::appName())));
  connect(trayIcon.get(), &QSystemTrayIcon::activated, this,
          &MainWindow::trayIconActivated);

  // 创建托盘菜单
  const auto trayMenu = new QMenu(this);
  const auto showAction = new QAction(tr("Show Window"), this);
  const auto quitAction = new QAction(tr("Quit"), this);
  connect(showAction, &QAction::triggered, this, &MainWindow::showNormal);
  connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
  trayMenu->addAction(showAction);
  trayMenu->addSeparator();
  trayMenu->addAction(quitAction);
  trayIcon->setContextMenu(trayMenu);
  // 显示系统托盘图标
  trayIcon->show();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::pushWidget2StackView(QWidget *widget) const {
  const auto stacked_widget = ui->stackedWidget;
  const auto cnt = stacked_widget->count();

  stacked_widget->addWidget(widget);
  stacked_widget->setCurrentIndex(cnt);
}

void MainWindow::goMonthView() {}

void MainWindow::closeEvent(QCloseEvent *event) {
  hide();
  event->ignore();
}

void MainWindow::trayIconActivated(
    const QSystemTrayIcon::ActivationReason reason) {
  if (reason == QSystemTrayIcon::DoubleClick)
    showNormal();
}
} // namespace touka
