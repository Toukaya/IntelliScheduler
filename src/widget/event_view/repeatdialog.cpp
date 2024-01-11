//
// Created by Touka on 2024/1/8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RepeatDialog.h" resolved

#include "repeatdialog.h"
#include "ui_RepeatDialog.h"

namespace touka {
RepeatDialog::RepeatDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::RepeatDialog) {
    ui->setupUi(this);
}

RepeatDialog::~RepeatDialog() {
    delete ui;
}
} // touka
