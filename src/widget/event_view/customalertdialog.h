//
// Created by Touka on 2024/1/10.
//

#ifndef CUSTOMALERTDIALOG_H
#define CUSTOMALERTDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class CustomAlertDialog; }
QT_END_NAMESPACE

class CustomAlertDialog : public QDialog {
Q_OBJECT

public:
    explicit CustomAlertDialog(QWidget *parent = nullptr);
    ~CustomAlertDialog() override;

private:
    Ui::CustomAlertDialog *ui;
};


#endif //CUSTOMALERTDIALOG_H
