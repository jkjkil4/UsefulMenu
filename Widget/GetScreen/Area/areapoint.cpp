#include "areapoint.h"

#include <QMouseEvent>

#include <QDebug>

AreaPoint::AreaPoint(int *x, int *y, QWidget *parent)
    : AreaParent(parent),
      pX(x), pY(y)
{
    limitSize(this, pointSize, pointSize);
}

void AreaPoint::onOtherMoved() {
    int toX = (pX ? *pX - pointRadius : x());
    int toY = (pY ? *pY - pointRadius : y());
    move(toX, toY);
}


void AreaPoint::onMouseMoving(QPoint pos) {
    bool isMoved = false;

    if(pX) {
        int xOffset = pos.x() - startPos.x();
        *pX += xOffset;
        isMoved = true;
    }
    if(pY) {
        int yOffset = pos.y() - startPos.y();
        *pY += yOffset;
        isMoved = true;
    }

    if(isMoved)
        emit moved();
}


void AreaPoint::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        onMouseMoving(ev->pos());
    }
}

void AreaPoint::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        onMouseMoving(ev->pos());
    }
}

void AreaPoint::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        emit released();
    }
}

void AreaPoint::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
}
