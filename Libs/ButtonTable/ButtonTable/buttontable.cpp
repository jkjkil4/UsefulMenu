#include "buttontable.h"

#define IsRectContains(point) QRect(0, 0, width(), height()).contains(point)

ButtonTable::ButtonTable(QWidget *parent) : QWidget(parent)
{
    connect(timerUpdateOffset, SIGNAL(timeout()), this, SLOT(onTimerUpdateOffset()));
    connect(timerCheckMouseOut, SIGNAL(timeout()), this, SLOT(onTimerCheckMouseOut()));

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

#define BT_VARIBLE_FUNC(FuncName, varName, Type)\
    Type ButtonTable::get##FuncName() const { return varName; }\
    void ButtonTable::set##FuncName(Type input_##varName) { varName = input_##varName; startTimerUpdate(); adjustWidth(); }

BT_VARIBLE_FUNC(BtnWidth, btnWidth, int)
BT_VARIBLE_FUNC(BtnHeight, btnHeight, int)
BT_VARIBLE_FUNC(BtnXCount, btnXCount, int)
BT_VARIBLE_FUNC(Spacing, spacing, int)
BT_VARIBLE_FUNC(Margin, margin, int)

#undef BT_VARIBLE_FUNC


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
    int min = qMin<int>(height() - ((btnHeight + spacing) * ((vItems.size() - 1) / btnXCount + 1) + 2 * margin - spacing), 0);
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


void ButtonTable::onTimerCheckMouseOut() {
    if(isHolding)
        return;

    if(!IsRectContains(mapFromGlobal(cursor().pos()))) {
        mouseIndex = -1;
        timerCheckMouseOut->stop();

        startTimerUpdate();
    }
}


void ButtonTable::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        isHolding = true;
        mouseIndex = getIndex(ev->pos());

        startTimerUpdate();
    }
}

void ButtonTable::mouseMoveEvent(QMouseEvent *ev) {
    if(!(ev->buttons() & Qt::LeftButton)) {
        if(!timerCheckMouseOut->isActive())
            timerCheckMouseOut->start(8);
        mouseIndex = getIndex(ev->pos());
    }

    startTimerUpdate();
}

void ButtonTable::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        if(mouseIndex != -1) {
            //int xPos = mouseIndex % btnXCount;
            //int yPos = mouseIndex / btnXCount;

            //int rectX = margin + xPos * (btnWidth + spacing);
            //int rectY = margin + yPos * (btnHeight + spacing);
            //if(QRect(rectX, rectY + yOffset, btnWidth, btnHeight).contains(ev->pos())) {
                emit clicked(vItems[mouseIndex]);
            //}
        }

        isHolding = false;
        mouseIndex = getIndex(ev->pos());

        startTimerUpdate();
    } else if(ev->button() == Qt::RightButton) {
        if(mouseIndex != -1) {
            QAction actMoveLeft("左移");
            QAction actMoveRight("右移");
            QAction actMoveUp("上移");
            QAction actMoveDown("下移");

            QMenu menu;
            menu.move(cursor().pos());
            menu.addActions(QList<QAction*>() << &actMoveLeft << &actMoveRight << &actMoveUp << &actMoveDown);
            emit appendAction(&menu, vItems[mouseIndex]);
            QAction* res = menu.exec();

            if(res) {
                if(res == &actMoveLeft) {
                    moveItem(mouseIndex, mouseIndex - 1);
                } else if(res == &actMoveRight) {
                    moveItem(mouseIndex, mouseIndex + 1);
                } else if(res == &actMoveUp) {
                    moveItem(mouseIndex, mouseIndex - btnXCount);
                } else if(res == &actMoveDown) {
                    moveItem(mouseIndex, mouseIndex + btnXCount);
                } else emit checkAction(res, vItems[mouseIndex]);
            }
        }
    }
}

void ButtonTable::wheelEvent(QWheelEvent *ev) {
    int num = ev->delta() / 10;
    if ((spd < 0 && num > 0) || (spd > 0 && num < 0))
            spd = 0;
    spd += num;
    if (abs(spd) > 16)
        spd > 0 ? spd = 16 : spd = -16;

    startTimerUpdateOffset();

    startTimerUpdate();
}

void ButtonTable::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor(102, 204, 255, 160));

    int yPosBegin = -yOffset / (btnHeight + spacing);
    int yPosEnd = (height() - yOffset) / (btnHeight + spacing);

    int iBegin = qMax(0, yPosBegin * btnXCount);
    int iEnd = qBound(0, (yPosEnd + 1) * btnXCount, vItems.size());
    for(int i = iBegin; i < iEnd; i++) {
        ButtonTableItem* item = vItems[i];

        int rectX = margin + (btnWidth + spacing) * (i % btnXCount);
        int rectY = margin + (btnHeight + spacing) * (i / btnXCount);

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
    int w = (btnWidth + spacing) * btnXCount - spacing + 2 * margin;
    setMinimumWidth(w);
    setMaximumWidth(w);
}

void ButtonTable::moveItem(int index, int toIndex) {
    int vSize = vItems.size();
    if(vSize == 0 || index < 0 || index >= vSize)
        return;
    toIndex = qBound(0, toIndex, vSize - 1);
    if(toIndex == index)
        return;
    ButtonTableItem *tmpItem = vItems[index];
    vItems[index] = vItems[toIndex];
    vItems[toIndex] = tmpItem;

    emit itemMoved(vItems[toIndex], vItems[index]);
}

void ButtonTable::addItem(ButtonTableItem *item) {
    vItems.append(item);
    startTimerUpdateOffset();
    startTimerUpdate();
}

void ButtonTable::removeItem(ButtonTableItem *item) {
    vItems.removeOne(item);
    delete item;
    startTimerUpdateOffset();
    startTimerUpdate();
}

void ButtonTable::clearItem() {
    for(auto item : vItems)
        delete item;
    vItems.clear();
    startTimerUpdateOffset();
    startTimerUpdate();
}

int ButtonTable::getIndex(QPoint mouse) {
    if(mouse.x() < margin)
        return -1;

    int xLocalPos = (mouse.x() - margin) % (btnWidth + spacing);
    if(xLocalPos > btnWidth)
        return -1;

    int yLocalPos = (mouse.y() - yOffset - margin) % (btnHeight + spacing);
    if(yLocalPos > btnHeight)
        return -1;

    int xPos = (mouse.x() - margin) / (btnWidth + spacing);
    if(xPos >= btnXCount)
        return -1;
    int yPos = (mouse.y() - yOffset - margin) / (btnHeight + spacing);

    int index = xPos + yPos * btnXCount;
    if(index < 0 || index >= vItems.size())
        return -1;

    return index;
}

void ButtonTable::startTimerUpdateOffset() {
    if(!timerUpdateOffset->isActive())
            timerUpdateOffset->start(16);
}

void ButtonTable::startTimerUpdate() {
    if(!timerUpdate->isActive())
        timerUpdate->start(timerDelayMs);
}
