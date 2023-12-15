//
// Created by Touka on 2023/12/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GridView.h" resolved

#include "gridview.h"

#include <QScrollBar>
#include <QPainter>
#include <QEvent>

namespace touka {
    GridView::GridView(int rows, int cols, int cellWidth, int cellHeight, QWidget *parent)
    : QAbstractScrollArea(parent), rows_(rows), cols_(cols),
    cell_width_(cellWidth), cell_height_(cellHeight) {
        Q_ASSERT(rows > 0);
        Q_ASSERT(cols > 0);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        horizontalScrollBar()->setRange(0, cols * getCellWidth());
        verticalScrollBar()->setRange(0, rows * getCellHeight());
    }

    GridView::~GridView()=default;

    int GridView::getCellWidth() const {
        if (cell_width_ > 0)
            return cell_width_;
        return width() / rows_;
    }

    void GridView::setcellWidth(const int cell_width) {
        cell_width_ = cell_width;
    }

    int GridView::getCellHeight() const {
        if (cell_height_ > 0)
            return cell_height_;
        return height() / cols_;
    }

    void GridView::setCellHeight(const int cell_height) {
        cell_height_ = cell_height;
    }

    bool GridView::viewportEvent(QEvent* event) {
        if (event->type() != QEvent::Paint) return QAbstractScrollArea::viewportEvent(event);
        QPainter painter(viewport());
        painter.setPen(QPen(Qt::black, 1));
        for(int i = 1; i < rows_; ++i) {
            painter.drawLine(0, i*getCellHeight() - verticalScrollBar()->value(), cols_*getCellWidth(), i*getCellHeight() - verticalScrollBar()->value());
        }
        for(int i = 1; i < cols_; ++i) {
            painter.drawLine(i*getCellWidth() - horizontalScrollBar()->value(), 0, i*getCellWidth() - horizontalScrollBar()->value(), rows_*getCellHeight());
        }
        return true;
    }

} // touka
