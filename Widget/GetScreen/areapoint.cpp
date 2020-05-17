#include "areapoint.h"

#include <QMouseEvent>

#include <QDebug>

AreaPoint::AreaPoint(int *x, int *y, QWidget *parent)
    : AreaParent(x, y, parent)
{
    limitSize(this, 5, 5);
}

void AreaPoint::onOtherMoved() {
    int toX = (pX ? *pX - 2 : x());
    int toY = (pY ? *pY - 2 : y());
    move(toX, toY);
}


void AreaPoint::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        startPos = ev->pos();
    }
}

void AreaPoint::mouseMoveEvent(QMouseEvent *ev) {
    QPoint pos = ev->pos();

    if(ev->buttons() & Qt::LeftButton) {
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
