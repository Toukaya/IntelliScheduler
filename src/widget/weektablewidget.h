//
// Created by Touka on 2023/12/13.
//

#ifndef INTELLISCHEDULER_WEEKTABLEWIDGET_H
#define INTELLISCHEDULER_WEEKTABLEWIDGET_H

#include <QTableWidget>

#include "types.hpp"

namespace touka {
    enum class Week;
    QT_BEGIN_NAMESPACE
    namespace Ui { class WeekTableWidget; }
    QT_END_NAMESPACE

    constexpr static int DOT_RADIUS = 5;
    constexpr static int TIME_DISPLAY_FONT_SIZE = 10;
    constexpr static int TIMER_RESTART_INTERVAL_MSEC = 60000;
    constexpr static int TIME_DISPLAY_Y_OFFSET = 4;
    constexpr static int GRID_HEIGHT = 60;

    /**
     * @brief A custom widget that represents a table for displaying weeks.
     *
     * This class is a subclass of QTableWidget and provides additional
     * functionality for displaying the current time as a scan line in the table.
     *
     * @note The optimal display conditions for this widget rely on the cell
     * height being set to 60px and the table column count being set to 24.
     * Any other settings can cause display issues.
     */
    class WeekTableWidget : public QTableWidget {
    Q_OBJECT

    public:
        /**
         * @brief A custom widget that represents a table for displaying weeks.
         *
         * This class is a subclass of QTableWidget and provides additional functionality for displaying the current time as a scan line in the table.
         */
        explicit WeekTableWidget(QWidget *parent = nullptr);

        ~WeekTableWidget() override;

        // TODO finish it
        void addEvtInfo(const QString &evtContext, const QTime &startTime, const QTime &endTime);
        void clearADaysEvtInfo(Week week);

    protected:

        bool viewportEvent(QEvent *event) override;

    protected slots:

        /**
         * @brief Updates the position of the scan line.
         *
         * Updates the position of the scan line used to display the current time
         * in the WeekTableWidget. If the scan line position exceeds the viewport height,
         * it resets the position and increments the number of weeks.
         *
         * @note This function assumes that the WeekTableWidget is created and its viewport is set.
         */
        void updateScanLinePosition();

    private:
        Ui::WeekTableWidget *ui;

        int scan_line_pos_;

        int todays_num_of_weeks_;

        /**
         * @brief Draws a line at the specified Y coordinate.
         *
         * This function draws a line using the given QPainter object at the specified Y coordinate.
         *
         * @param painter The QPainter object used for drawing.
         * @param pointY The Y coordinate at which the line should be drawn.
         *
         * @note The optimal display conditions for this widget rely on the cell height being set to 60px and the table column count being set to 24.
         * Any other settings can cause display issues.
         */
        void drawLine(QPainter &painter, int pointY) const;

        /**
         * @brief Draws a dot at the specified coordinates.
         *
         * This function draws a dot using the given QPainter object at the specified
         * coordinates (pointX, pointY).
         *
         * @param painter The QPainter object used for drawing.
         * @param pointY The Y coordinate at which the dot should be drawn.
         * @param pointX The X coordinate at which the dot should be drawn.
         *
         * @note The optimal display conditions for this widget rely on the cell height being set to 60px and the table column count being set to 24.
         * Any other settings can cause display issues.
         */
        static void drawDot(QPainter &painter, int pointY, int pointX) ;

        /**
         * @brief Draws the current time in the WeekTableWidget at the specified coordinates.
         *
         * This function draws the current time in the WeekTableWidget using the given QPainter object.
         * The current time is displayed as text at the specified coordinates (pointX, pointY).
         *
         * @param painter The QPainter object used for drawing.
         * @param pointY The Y coordinate at which the current time should be displayed.
         * @param pointX The X coordinate at which the current time should be displayed.
         *
         * @note The optimal display conditions for this widget rely on the cell height being set to 60px and the table column count being set to 24.
         * Any other settings can cause display issues.
         */
        static void drawCurrentTime(QPainter &painter, int pointY, int pointX) ;
    };
} // touka

#endif //INTELLISCHEDULER_WEEKTABLEWIDGET_H
