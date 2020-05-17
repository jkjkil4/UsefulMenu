#include "verareapoint.h"

#include <QMouseEvent>

VerAreaPoint::VerAreaPoint(int *pY, int *pX1, int *pX2, QWidget *parent)
    : AreaParent(parent),
      pY(pY), pX1(pX1), pX2(pX2)
{
    limitSize(this, 5, 5);
    setCursor(Qt::SizeVerCursor);
}

void VerAreaPoint::onOtherMoved() {
    int toX = (*pX1 + *pX2) / 2 - 2;
    int toY = *pY - 2;
    move(toX, toY);
}


void VerAreaPoint::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        startY = ev->y();
    }
}

void VerAreaPoint::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        int yOffset = ev->y() - startY;
        *pY += yOffset;
        emit moved();
    }
}

void VerAreaPoint::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        emit released();
    }
}

void VerAreaPoint::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
}
