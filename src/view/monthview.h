//
// Created by Touka on 2023/12/4.
//

#ifndef MONTHVIEW_H
#define MONTHVIEW_H

#include <QWidget>

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui { class MonthView; }
QT_END_NAMESPACE

class MonthView : public QWidget {
Q_OBJECT

public:
    explicit MonthView(QWidget *parent = nullptr);
    ~MonthView() override;

private:
    Ui::MonthView *ui;
};
} // touka

#endif //MONTHVIEW_H
