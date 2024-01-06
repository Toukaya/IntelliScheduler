//
// Created by Touka on 2023/12/20.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_CategoryComboBox.h" resolved

#include "categorycombobox.h"

#include <QtGui/qpen.h>
#include <qpainter.h>
#include <qpainterpath.h>

#include "entity/EventCategories.h"

// #include "ui_CategoryComboBox.h"

namespace touka {
CategoryComboBox::CategoryComboBox(QWidget *parent) : QComboBox(parent) {}

void CategoryComboBox::addCategory(const EventCategories &category) {
  const auto color = category.getColor();
  const int size = font().pointSize();
  constexpr int radius = 1;
  constexpr float borderWidth = 1;

  QPixmap pixmap(size, size);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);
  QRectF rect(borderWidth, borderWidth, size - 2 * borderWidth,
              size - 2 * borderWidth);

  QPainterPath path;
  path.addRoundedRect(rect, radius, radius);

  painter.setPen(QPen(color.darker(), borderWidth));
  // i dont konw why those num...
  painter.drawRoundedRect(rect.adjusted(-borderWidth / 2, -borderWidth / 2,
                                        borderWidth / 4, borderWidth / 4),
                          radius, radius);

  painter.fillPath(path, QBrush(color));
  addItem(QIcon(pixmap), category.getName());
}

CategoryComboBox::~CategoryComboBox() = default;
} // namespace touka
