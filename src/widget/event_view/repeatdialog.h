//
// Created by Touka on 2024/1/8.
//

#ifndef REPEATDIALOG_H
#define REPEATDIALOG_H

#include <QDialog>

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui { class RepeatDialog; }
QT_END_NAMESPACE

class RepeatDialog : public QDialog {
Q_OBJECT

public:
    explicit RepeatDialog(QWidget *parent = nullptr);
    ~RepeatDialog() override;

private:
    Ui::RepeatDialog *ui;
};
} // touka

#endif //REPEATDIALOG_H
