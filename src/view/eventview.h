//
// Created by Touka on 2023/12/17.
//

#ifndef EVENTVIEW_H
#define EVENTVIEW_H

#include <QWidget>

#include "types.hpp"

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui { class EventView; }
QT_END_NAMESPACE

    constexpr static int8 TRIANGLE_HEIGHT = 12;
    constexpr static int8 TRIANGLE_HALF_WEIGHT = 12;
    constexpr static Color BACKGROUND_COLOR = QColor(240, 240, 240);

class EventView : public QWidget {
Q_OBJECT

public:
    explicit EventView(bool isWindow, QWidget *parent = nullptr);
    ~EventView() override;

public slots:

    static void menu(/*TODO Event infomation param*/QPoint pos, QWidget *parent);

protected:
    void paintEvent(QPaintEvent* event) override;

    void focusOutEvent(QFocusEvent* event) override;

private:

    explicit EventView(QWidget *parent = nullptr);

    Ui::EventView *ui;

    bool is_windows_;
};
} // touka

#endif //EVENTVIEW_H
