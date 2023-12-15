//
// Created by Touka on 2023/12/15.
//

#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QAbstractScrollArea>

class QStandardItemModel;

namespace touka {

    class GridView : public QAbstractScrollArea {
        Q_OBJECT

        public:
        explicit GridView(int rows, int cols, int cellWidth, int cellHeight, QWidget *parent = nullptr);
        ~GridView() override;

        [[nodiscard]] int getCellWidth() const;

        void setcellWidth(int cell_width);

        [[nodiscard]] int getCellHeight() const;

        void setCellHeight(int cell_height);

    protected:
        bool viewportEvent(QEvent*) override;

    private:
        int rows_;
        int cols_;
        int cell_width_;
        int cell_height_;
    };
} // touka

#endif //GRIDVIEW_H
