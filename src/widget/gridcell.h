//
// Created by Touka on 2023/12/8.
//

#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <QFrame>

#include "types.hpp"

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui { class GridCell; }
QT_END_NAMESPACE

class GridCell : public QFrame {
Q_OBJECT

public:
    explicit GridCell(QWidget *parent = nullptr);
    ~GridCell() override;

private:
    Ui::GridCell *ui;
    std::shared_ptr<Date> date_;
};
} // touka

#endif //GRIDCELL_H
