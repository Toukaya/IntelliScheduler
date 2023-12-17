//
// Created by Touka on 2023/12/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MonthView.h" resolved

#include "monthview.h"

#include <QtCore/qdatetime.h>
#include <QtWidgets/QPushButton>

#include "ui_MonthView.h"
#include "utils/DateUtil.h"

#include "widget/gridcell.h"

namespace touka {
MonthView::MonthView(QWidget *parent) :
    QWidget(parent), ui(new Ui::MonthView) {
    ui->setupUi(this);
    const auto currDate = QDate::currentDate();
    curr_year_ = currDate.year();
    curr_month_ = static_cast<Month>(currDate.month());

    initTable();
    initDateLabels();
    ui->lbDate->setText(getDateTitle());

    connect(ui->btnPrevMonth, &QPushButton::clicked, this, [&] {
        const auto date = Date(curr_year_, MONTH_TO_INT_TOUKA(curr_month_), 1).addMonths(-1);
        navigateTo(date.year(), static_cast<Month>(date.month()));
    });
    connect(ui->btnNextMonth, &QPushButton::clicked, this, [&] {
        const auto date = Date(curr_year_, MONTH_TO_INT_TOUKA(curr_month_), 1).addMonths(1);
        navigateTo(date.year(), static_cast<Month>(date.month()));
    });
    connect(ui->btnToday, &QPushButton::clicked, this, [&] {
        const auto date = QDate::currentDate();
        navigateTo(date.year(), static_cast<Month>(date.month()));
    });
}


MonthView::~MonthView() {
    delete ui;
}

Date MonthView::getCurrentMonthFirstDay() {
    return {curr_year_, MONTH_TO_INT_TOUKA(curr_month_), 1};
}

inline void MonthView::initTable() const {
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

inline void MonthView::initDateLabels() {
    const auto table = ui->tableWidget;
    auto currDate = getCurrentMonthFirstDay();
    const int dayOfWeek = currDate.dayOfWeek();
    currDate = currDate.addDays(-dayOfWeek);
    const int month = MONTH_TO_INT_TOUKA(curr_month_);

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            auto *cell = new GridCell(currDate, this);
            cell->setActivate(currDate.month() == month);
            table->setCellWidget(i, j, cell);
            currDate = currDate.addDays(1);
        }
    }
}

void MonthView::updateDateLabels() {
    const auto table = ui->tableWidget;
    auto currDate = getCurrentMonthFirstDay();
    const int dayOfWeek = currDate.dayOfWeek();
    currDate = currDate.addDays(-dayOfWeek);
    const int month = MONTH_TO_INT_TOUKA(curr_month_);

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            auto cell = dynamic_cast<GridCell*>(table->cellWidget(i, j));
            cell->setDate(currDate);
            cell->setActivate(currDate.month() == month);
            currDate = currDate.addDays(1);
        }
    }
}

void MonthView::refresh() {
    updateDateLabels();
    ui->lbDate->setText(getDateTitle());
}

void MonthView::navigateTo(int year, Month month) {
    curr_year_ = year;
    curr_month_ = month;
    refresh();
}

QString MonthView::getDateTitle() const {
    return QString("<html><head/><body><p><span style=\" font-size:32pt; font-weight:700;\">"
                     "%1"
                     "</span><span style=\" font-size:32pt;\"> "
                     "%2"
                     "</span></p></body></html>").arg(DateUtil::getLiteralMonth(curr_month_), QString::number(curr_year_));
}
} // touka
