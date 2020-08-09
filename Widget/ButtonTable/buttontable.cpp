#include "buttontable.h"

ButtonTable::ButtonTable(QWidget *parent) : QWidget(parent)
{

}

ButtonTable::~ButtonTable() {
    for(auto item : vItems)
        delete item;
    vItems.clear();
}


void ButtonTable::mousePressEvent(QMouseEvent *ev) {
    mouseIndex = getIndex(ev->pos());
    isHolding = true;
}

void ButtonTable::mouseMoveEvent(QMouseEvent *ev) {

}

void ButtonTable::mouseReleaseEvent(QMouseEvent *ev) {
    isHolding = false;
}

void ButtonTable::wheelEvent(QWheelEvent *ev) {
    yOffset += ev->y() / 20;
}

void ButtonTable::paintEvent(QPaintEvent*) {

}


void ButtonTable::adjustWidth() {
    resize((btnWidth + btnSpacing) * btnXCount - btnSpacing + 2 * margin, height());
}

void ButtonTable::addItem(ButtonTableItem *item) {
    vItems.append(item);
}

int ButtonTable::getIndex(QPoint mouse) {
    //在按钮中的相对位置(x)
    int xLocalPos = (mouse.x() - margin) % (btnWidth + btnSpacing);
    if(xLocalPos > btnWidth)    //如果不在按钮内
        return -1;  //返回-1

    //在按钮中的相对位置(y)
    int yLocalPos = (mouse.y() - yOffset - margin) % (btnHeight + btnSpacing);
    if(yLocalPos > btnHeight) //如果不在按钮内
        return -1;  //返回-1

    int xPos = (mouse.x() - margin) / (btnWidth + btnSpacing);
    if(xPos > btnXCount)
        return -1;
    int yPos = (mouse.y() - yOffset - margin) / (btnHeight + btnSpacing);

    int index = xPos + yPos * btnXCount;
    if(index < 0 || index >= vItems.size())
        return -1;

    return index;
}
