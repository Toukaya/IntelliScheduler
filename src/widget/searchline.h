//
// Created by Touka on 2023/12/11.
//

#ifndef SEARCHLINE_H
#define SEARCHLINE_H

#include <QLineEdit>

namespace touka {
QT_BEGIN_NAMESPACE
namespace Ui { class SearchLine; }
QT_END_NAMESPACE

class SearchLine : public QLineEdit {
Q_OBJECT

public:
    explicit SearchLine(QWidget *parent = nullptr);
    ~SearchLine() override;

private:
    Ui::SearchLine *ui;
};
} // touka

#endif //SEARCHLINE_H
