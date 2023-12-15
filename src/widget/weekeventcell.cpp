//
// Created by Touka on 2023/12/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WeekEventCell.h" resolved

#include "weekeventcell.h"
#include "entity/Event.h"

#include <QtWidgets/QGridLayout>

#include "ui_WeekEventCell.h"
#include "weekevtcelllabel.h"

namespace touka {
    WeekEventCell::WeekEventCell(QWidget *parent) :
            QWidget(parent), ui(new Ui::WeekEventCell) {
        ui->setupUi(this);
        QGridLayout *gridLayout = new QGridLayout();
    }

    WeekEventCell::~WeekEventCell() {
        delete ui;
    }

    void WeekEventCell::update() {
    }

    void WeekEventCell::addEvent(const std::shared_ptr<Event>& evt) {
        if (!evt) return;
        auto label = new WeekEvtCellLabel(this);
        auto color = evt->getCategories().getColor();
        label->setColor(color);

        // auto height =
        // label->setFixedHeight()
    }

    void WeekEventCell::removeEvent(std::shared_ptr<Event> evt) {
    }
} // touka
