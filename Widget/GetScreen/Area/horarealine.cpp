#include "horarealine.h"

HorAreaLine::HorAreaLine(int *pX, int *pY1, int *pY2, QWidget *parent)
    : HorAreaPoint(pX, pY1, pY2, parent) {}

void HorAreaLine::onInit() {
    limitWidth(this, 1);
}

void HorAreaLine::onOtherMoved() {
    int toX = *pX;
    int toY = qMin(*pY1, *pY2);
    int toH = qAbs(*pY1 - *pY2) + 1;
    setGeometry(toX, toY, 1, toH);
}
