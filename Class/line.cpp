#include "line.h"

Line::Line(Qt::Orientation ori, QColor color, QWidget *parent)
    : QWidget(parent), color(color)
{
    switch((int)ori) {
    case Qt::Horizontal:
        limitHeight(this, 1);
        break;
    case Qt::Vertical:
        limitWidth(this, 1);
        break;
    }
}

void Line::paintEvent(QPaintEvent *) {
    QPainter p(this);

    p.fillRect(0, 0, width(), height(), color);
}
