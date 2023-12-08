//
// Created by Touka on 2023/12/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MonthView.h" resolved

#include "monthview.h"

#include <QtCore/qdatetime.h>

#include "ui_MonthView.h"

#include "widget/gridcell.h"

namespace touka {
MonthView::MonthView(QWidget *parent) :
    QWidget(parent), ui(new Ui::MonthView) {
    ui->setupUi(this);
    ui->gridLayout->setContentsMargins(0, 0, 0, 0);
    ui->gridLayout->setSpacing(0);


    // TODO: this is tmp code
    curr_year_ = 2001;
    curr_month_ = 5;

    setDateLabels();
}

MonthView::~MonthView() {
    delete ui;
}

void MonthView::setDateLabels() {
    const auto layout = ui->gridLayout;
    for (int i = 1; i <= 6; ++i) {
        for (int j = 1; j <= 7; ++j) {
            auto cell = new GridCell(this);
            layout->addWidget(cell, i, j);
        }
    }
}
} // touka
