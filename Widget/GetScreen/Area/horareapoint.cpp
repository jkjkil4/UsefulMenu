#include "horareapoint.h"

#include <QMouseEvent>

HorAreaPoint::HorAreaPoint(int *pX, int *pY1, int *pY2, QWidget *parent)
    : AreaParent(parent),
      pX(pX), pY1(pY1), pY2(pY2)
{
    limitSize(this, 5, 5);
    setCursor(Qt::SizeHorCursor);
}


void HorAreaPoint::onOtherMoved() {
    int toX = *pX - 2;
    int toY = (*pY1 + *pY2) / 2 - 2;
    move(toX, toY);
}


void HorAreaPoint::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        startX = ev->x();
    }
}

void HorAreaPoint::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        int xOffset = ev->x() - startX;
        *pX += xOffset;
        emit moved();
    }
}

void HorAreaPoint::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        emit released();
    }
}


void HorAreaPoint::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
}
