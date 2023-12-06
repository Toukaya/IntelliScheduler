//
// Created by Touka on 2023/12/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MonthView.h" resolved

#include "monthview.h"
#include "ui_MonthView.h"

namespace touka {
MonthView::MonthView(QWidget *parent) :
    QWidget(parent), ui(new Ui::MonthView) {
    ui->setupUi(this);
}

MonthView::~MonthView() {
    delete ui;
}
} // touka
