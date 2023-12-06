//
// Created by Touka on 2023/12/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DateGridWidget.h" resolved

#include "dategridwidget.h"
#include "ui_DateGridWidget.h"

namespace touka {
DateGridWidget::DateGridWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::DateGridWidget) {
    ui->setupUi(this);
}

DateGridWidget::~DateGridWidget() {
    delete ui;
}

// void DateGridWidget::paintEvent(QPaintEvent* event) {
//     QWidget::paintEvent(event);
// }
} // touka
