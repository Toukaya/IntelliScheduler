//
// Created by Touka on 2023/12/13.
//

#ifndef INTELLISCHEDULER_WEEKEVTCELLLABEL_H
#define INTELLISCHEDULER_WEEKEVTCELLLABEL_H

#include <QLabel>
#include <QTime>

namespace touka {
    QT_BEGIN_NAMESPACE
    namespace Ui { class WeekEvtCellLabel; }
    QT_END_NAMESPACE

    class WeekEvtCellLabel : public QFrame {
        Q_OBJECT

    public:
        explicit WeekEvtCellLabel(QWidget *parent = nullptr);

        ~WeekEvtCellLabel() override;

        void bindEvt();

    public slots:

        void setTime(const QTime &time) const;

        void setContext(const QString &context) const;

        void setColor(const QColor &color);

    protected:

        void paintEvent(QPaintEvent*) override;

        void resizeEvent(QResizeEvent* event) override;

    private:
        Ui::WeekEvtCellLabel *ui;

        QColor background_color_;
    };
} // touka

#endif //INTELLISCHEDULER_WEEKEVTCELLLABEL_H
