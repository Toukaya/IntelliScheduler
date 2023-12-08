//
// Created by Touka on 2023/12/8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GridCell.h" resolved

#include "gridcell.h"

#include <QtCore/qdatetime.h>

#include "ui_GridCell.h"

namespace touka {
GridCell::GridCell(QWidget *parent) :
    QFrame(parent), ui(new Ui::GridCell) {
    ui->setupUi(this);
}

// GridCell::GridCell(std::shared_ptr<Date> date, QWidget* parent) :
//     QFrame(parent), ui(new Ui::GridCell), date_(std::move(date)) {
//     ui->setupUi(this);
//     ui->lbDate->setText(date_->toString("dd"));
// }

GridCell::~GridCell() {
    delete ui;
}
} // touka
