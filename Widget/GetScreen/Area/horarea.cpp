#include "horarea.h"

#include <QMouseEvent>

HorArea::HorArea(Type type, int *pX, int *pY1, int *pY2, QWidget *parent)
    : AreaParent(parent),
      type(type), pX(pX), pY1(pY1), pY2(pY2)
{
    if(type == Point) {
        limitSize(this, 5, 5);
    }
    else {
        limitWidth(this, 1);
    }
    setCursor(Qt::SizeHorCursor);
}

void HorArea::onOtherMoved() {
    if(type == Point) {
        int toX = *pX - 2;
        int toY = (*pY1 + *pY2) / 2 - 2;
        move(toX, toY);
    }
    else {
        int toX = *pX;
        int toY = qMin(*pY1, *pY2);
        int toH = qAbs(*pY1 - *pY2) + 1;
        setGeometry(toX, toY, 1, toH);
    }
}


void HorArea::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        startX = ev->x();
    }
}

void HorArea::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        int xOffset = ev->x() - startX;
        *pX += xOffset;
        emit moved();
    }
}

void HorArea::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        emit released();
    }
}


void HorArea::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
}
