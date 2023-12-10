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
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // TODO: this is tmp code
    curr_year_ = 2001;
    curr_month_ = 5;

    setDateLabels();
}

MonthView::~MonthView() {
    delete ui;
}

void MonthView::setDateLabels() {
    const auto table = ui->tableWidget;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            auto cell = new GridCell(this);
            table->setCellWidget(i, j, cell);
        }
    }
}
} // touka
