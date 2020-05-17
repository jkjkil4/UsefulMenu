#include "verarea.h"

#include <QMouseEvent>

VerArea::VerArea(Type type, int *pY, int *pX1, int *pX2, QWidget *parent)
    : AreaParent(parent),
      type(type), pY(pY), pX1(pX1), pX2(pX2)
{
    if(type == Point) {
        limitSize(this, 5, 5);
        startY = pointRadius;
    }
    else {
        startY = 0;
        limitHeight(this, 1);
    }
    setCursor(Qt::SizeVerCursor);
}

void VerArea::onOtherMoved() {
    if(type == Point) {
        int toX = (*pX1 + *pX2) / 2 - pointRadius;
        int toY = *pY - pointRadius;
        move(toX, toY);
    }
    else {
        int toX = qMin(*pX1, *pX2);
        int toY = *pY;
        int toW = qAbs(*pX1 - *pX2) + 1;
        setGeometry(toX, toY, toW, 1);
    }
}


void VerArea::onMouseMoving(int y) {
    int yOffset = y - startY;
    *pY += yOffset;
    emit moved();
}


void VerArea::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        onMouseMoving(ev->y());
    }
}

void VerArea::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        onMouseMoving(ev->y());
    }
}

void VerArea::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        emit released();
    }
}

void VerArea::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
}
