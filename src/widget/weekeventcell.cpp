//
// Created by Touka on 2023/12/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WeekEventCell.h" resolved

#include "weekeventcell.h"
#include "ui_WeekEventCell.h"

namespace touka {
    WeekEventCell::WeekEventCell(QWidget *parent) :
            QWidget(parent), ui(new Ui::WeekEventCell) {
        ui->setupUi(this);
    }

    WeekEventCell::~WeekEventCell() {
        delete ui;
    }
} // touka
