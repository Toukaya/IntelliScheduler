//
// Created by Touka on 2023/12/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SearchLine.h" resolved

#include "searchline.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

#include "ui_SearchLine.h"

namespace touka {
SearchLine::SearchLine(QWidget *parent) :
    QLineEdit(parent), ui(new Ui::SearchLine) {
    ui->setupUi(this);

    const auto layout = new QHBoxLayout(this);
    const auto iconLabel = new QLabel(this);
    const QIcon icon(":/icon/resource/icon/search.svg");
    const auto pixmap = icon.pixmap(QSize(16, 16), QIcon::Normal, QIcon::On);

    iconLabel->setPixmap(pixmap);
    iconLabel->setFixedSize(16,16);

    layout->addWidget(iconLabel);
    layout->addStretch(0);
    layout->setContentsMargins(4,0,0,0);
    setPlaceholderText(tr("Search"));
    setTextMargins(20,0,3,0);
    setContentsMargins(0,0,0,0);
    setLayout(layout);
}

SearchLine::~SearchLine() {
    delete ui;
}
} // touka
