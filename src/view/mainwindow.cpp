//
// Created by Touka on 2023/12/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"

#include "monthview.h"
#include "weekview.h"
#include "ui_MainWindow.h"

namespace touka {
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // TODO: remove this test code
    month_view_ = std::make_unique<MonthView>();
    week_view_ = std::make_unique<WeekView>();
    pushWidget2StackView(week_view_.get());

    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::pushWidget2StackView(QWidget* widget) const {
    const auto stacked_widget = ui->stackedWidget;
    const auto cnt = stacked_widget->count();

    stacked_widget->addWidget(widget);
    stacked_widget->setCurrentIndex(cnt);
}

void MainWindow::goMonthView() {

}
} // touka
