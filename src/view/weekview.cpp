//
// Created by Touka on 2023/12/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WeekView.h" resolved

#include <QScrollBar>
#include <QTimer>
#include <QTime>
#include "weekview.h"
#include "ui_WeekView.h"
#include "utils/DateUtil.h"

namespace touka {
    WeekView::WeekView(QWidget *parent) :
            QWidget(parent), ui(new Ui::WeekView) {
        ui->setupUi(this);

        initTable();
    }

    WeekView::~WeekView() {
        delete ui;
    }

    void WeekView::initTable() {
        constexpr auto initEvtTable = [](QTableWidget* tableWidget, int rowHeight) {
            tableWidget->setColumnCount(7);
            tableWidget->setRowCount(rowHeight);
            tableWidget->setColumnCount(7);
            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            tableWidget->verticalHeader()->setDefaultAlignment(Qt::AlignTop | Qt::AlignHCenter);
            tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section { color: #BDBDBD; background-color: #fff; border: node; padding-top: 4px; }");
            tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
            tableWidget->verticalHeader()->setFixedWidth(42);
            tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        };
        initEvtTable(ui->twEvt, 24);
        initEvtTable(ui->twAllDayEvt, 1);

        QFont font;
        font.setPointSize(10);
        for (int i = 0; i < 24; ++i) {
            QString timeText = QString("%1:00").arg(i, 2, 10, QChar('0'));
            auto headerItem = new QTableWidgetItem(timeText);
            headerItem->setFont(font);

            ui->twEvt->setVerticalHeaderItem(i, headerItem);
        }

        auto currTime = QTime::currentTime();
        int centerLineY = currTime.hour() * 60 + currTime.minute() - ui->twEvt->viewport()->height() / 2;
        ui->twEvt->verticalScrollBar()->setValue(centerLineY);

        auto headerItem = new QTableWidgetItem("all-day");
        headerItem->setFont(font);
        ui->twAllDayEvt->setVerticalHeaderItem(0, headerItem);

        // set splitter
        QList<int> sizes;
        sizes << 2 << 1000;
        ui->splitter->setSizes(sizes);
    }

    void WeekView::refresh() {

    }

    void WeekView::navigateTo(int year, Month month, Week week) {

    }

    void WeekView::scanLineUpdate() {

    }
} // touka
