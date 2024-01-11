//
// Created by Touka on 2024/1/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CustomAlertDialog.h" resolved

#include "customalertdialog.h"
#include "ui_CustomAlertDialog.h"


CustomAlertDialog::CustomAlertDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::CustomAlertDialog) {
    ui->setupUi(this);
}

CustomAlertDialog::~CustomAlertDialog() {
    delete ui;
}
