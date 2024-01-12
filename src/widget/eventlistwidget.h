//
// Created by Touka on 2024/1/9.
//

#ifndef EVENTLISTWIDGET_H
#define EVENTLISTWIDGET_H

#include <QListWidget>
#include <unordered_set>

#include "types.hpp"
#include "entity/Event.h"

namespace touka {
    class EventListItem;
}

class QLabel;

namespace touka {

    constexpr int16 LABEL_HEIGHT = 16;

class EventListWidget : public QListWidget {
Q_OBJECT

public:
    explicit EventListWidget(QWidget *parent = nullptr);
    ~EventListWidget() override;

public slots:
    void addEvent(const EventPtr& evt);

    void addEvents(const EventPtrList& evts);

    void clearEvent();

    void setEvents(const EventPtrList& evts);

    QString removeEvt(int idx);

protected:
    void mousePressEvent(QMouseEvent* event) override;

    void mouseDoubleClickEvent(QMouseEvent* event) override;

    // void contextMenuEvent(QContextMenuEvent*) override;

    void resizeEvent(QResizeEvent* e) override;

    void focusOutEvent(QFocusEvent* event) override;

private:

    void refresh();

    void update() const;

    std::vector<EventListItem*> labels_;

    // std::unordered_set<String> uids_;

    QLabel* label_more_{};
};
} // touka

#endif //EVENTLISTWIDGET_H
