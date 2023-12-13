//
// Created by Touka on 2023/12/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WeekEvtCellLabel.h" resolved

#include "weekevtcelllabel.h"
#include "ui_WeekEvtCellLabel.h"

namespace touka {
    WeekEvtCellLabel::WeekEvtCellLabel(QWidget *parent) :
            QLabel(parent), ui(new Ui::WeekEvtCellLabel) {
        ui->setupUi(this);
    }

    WeekEvtCellLabel::~WeekEvtCellLabel() {
        delete ui;
    }
} // touka
