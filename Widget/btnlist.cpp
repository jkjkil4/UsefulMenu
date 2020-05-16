#include "btnlist.h"

#include <QPainter>

BtnList::BtnList(QWidget *parent) : QWidget(parent) {}

void BtnList::updateChildsPos() {
    int offset = 0;
    QList<QWidget*> list = findChildren<QWidget*>();
    for(auto child : list) {
        int childX = (width() - child->width()) / 2;
        int childY = start + offset;
        child->move(childX, childY);
        offset += child->height() + spacing;
    }
    suitableHeight = start + offset + 10;
    resize(width(), suitableHeight);
}

void BtnList::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    p.setPen(QColor(190,190,190));
    p.setBrush(QColor(230,230,230));
    int r = qMin(width(), height()) / 2;
    p.drawRoundedRect(QRect(0, 0, width() - 1, height() - 1), r, r);
}
