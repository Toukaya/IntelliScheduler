//
// Created by touka on 2023/12/4.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_CanlendarWidget.h" resolved

#include "canlendarwidget.h"
#include "ui_CanlendarWidget.h"

namespace touka {
CanlendarWidget::CanlendarWidget(QWidget *parent)
    : QCalendarWidget(parent), ui(new Ui::CanlendarWidget) {
  ui->setupUi(this);
}

CanlendarWidget::~CanlendarWidget() { delete ui; }
} // namespace touka
