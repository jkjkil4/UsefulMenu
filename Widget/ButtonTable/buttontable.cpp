#include "buttontable.h"

ButtonTable::ButtonTable(QWidget *parent) : QWidget(parent)
{
    repeat(i, 40) {
        addItem(new ButtonTableItem);
    }

    connect(timerUpdateOffset, SIGNAL(timeout()), this, SLOT(onTimerUpdateOffset()));

    timerUpdate->setSingleShot(true);
    connect(timerUpdate, &QTimer::timeout, [=]{ update(); });

    setMouseTracking(true);
    adjustWidth();
}

ButtonTable::~ButtonTable() {
    for(auto item : vItems)
        delete item;
    vItems.clear();
}


void ButtonTable::onTimerUpdateOffset() {
    if (spd != 0) {
        //sumSpdToOffset
        yOffset += spd;
        if (spd > 0) {
            spd -= 1;
            if (spd < 0)
                spd = 0;
        }
        else if (spd < 0) {
            spd += 1;
            if (spd > 0)
                spd = 0;
        }
    }

    bool isMoving = false;
    int min = qMin<int>(height() - ((btnHeight + btnSpacing) * (vItems.size() / btnXCount) + 2 * margin - btnSpacing), 0);
    if (yOffset > 0 || yOffset < min) {
        //isMoving = limitOffset(min);
        //limitOffset
        if (yOffset > 0) {
            int limitSpd = 2 + yOffset / 4;
            yOffset -= limitSpd;
            if (yOffset < 0)
                yOffset = 0;
            isMoving = true;
        } else if (yOffset < min) {
            int limitSpd = 2 + (min - yOffset) / 4;
            yOffset += limitSpd;
            if (yOffset > min)
                yOffset = min;
            isMoving = true;
        } else isMoving = false;
    }

    mouseIndex = getIndex(mapFromGlobal(cursor().pos()));
    startTimerUpdate();

    if(spd == 0 && !isMoving)
        timerUpdateOffset->stop();
}


void ButtonTable::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        isHolding = true;
        mouseIndex = getIndex(ev->pos());

        startTimerUpdate();
    }
}

void ButtonTable::mouseMoveEvent(QMouseEvent *ev) {
    if(!(ev->buttons() & Qt::LeftButton))
        mouseIndex = getIndex(ev->pos());

    startTimerUpdate();
}

void ButtonTable::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        isHolding = false;
        mouseIndex = getIndex(ev->pos());

        startTimerUpdate();
    }
}

void ButtonTable::wheelEvent(QWheelEvent *ev) {
    int num = ev->delta() / 20;
    if ((spd < 0 && num > 0) || (spd > 0 && num < 0))
            spd = 0;
    spd += num;
    if (abs(spd) > 8)
        spd > 0 ? spd = 8 : spd = -8;

    if(!timerUpdateOffset->isActive())
            timerUpdateOffset->start(16);

    startTimerUpdate();
}

void ButtonTable::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor(102, 204, 255, 160));

    int yPosBegin = -yOffset / (btnHeight + btnSpacing);
    int yPosEnd = (height() - yOffset) / (btnHeight + btnSpacing);
    qDebug() << yOffset << yPosBegin << yPosEnd;
    int iBegin = qMax(0, yPosBegin * btnXCount);
    int iEnd = qBound(0, (yPosEnd + 1) * btnXCount, vItems.size());
    for(int i = iBegin; i < iEnd; i++) {
        ButtonTableItem* item = vItems[i];

        int rectX = margin + (btnWidth + btnSpacing) * (i % btnXCount);
        int rectY = margin + (btnHeight + btnSpacing) * (i / btnXCount);

        ButtonTableItem::ButtonFlag flag = ButtonTableItem::ButtonFlag::None;
        if(mouseIndex == i) {
            flag = isHolding
                    ? ButtonTableItem::ButtonFlag::MouseHolding
                    : ButtonTableItem::ButtonFlag::MouseAt;
        }

        item->onPaint(p, QRect(rectX, rectY + yOffset, btnWidth, btnHeight), flag);
    }
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
    if(xPos >= btnXCount)
        return -1;
    int yPos = (mouse.y() - yOffset - margin) / (btnHeight + btnSpacing);

    int index = xPos + yPos * btnXCount;
    if(index < 0 || index >= vItems.size())
        return -1;

    return index;
}

void ButtonTable::startTimerUpdate() {
    if(!timerUpdate->isActive())
        timerUpdate->start(timerDelayMs);
}
