//
// Created by Touka on 2023/12/4.
//

#ifndef DATEGRIDWIDGET_H
#define DATEGRIDWIDGET_H

#include <QWidget>

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui { class DateGridWidget; }
QT_END_NAMESPACE

class DateGridWidget : public QWidget {
Q_OBJECT

public:
    explicit DateGridWidget(QWidget *parent = nullptr);
    ~DateGridWidget() override;

// protected:
//     void paintEvent(QPaintEvent* event) override;

private:
    Ui::DateGridWidget *ui;
};
} // touka

#endif //DATEGRIDWIDGET_H
