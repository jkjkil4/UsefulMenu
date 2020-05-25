#include "pathsview.h"

PathsView::PathsView(QList<PathBtn*> *paths, QWidget *parent)
    : QWidget(parent),
      paths(paths)
{
    connect(ptimer, SIGNAL(timeout()), this, SLOT(slotTimer()));

    //设置属性
    limitSize(this, totalWidth, totalHeight);
}



void PathsView::slotTimer() {
    if (spd != 0)
        sumSpdToOffset();

    bool isMoving = false;
    int min = qMin<int>(height() - (PathBtn::bHeight + spacing) * getBlockYNum() - spacing, 0);
    if (offset > 0 || offset < min)
        isMoving = limitOffset(min);

    updateChildPos();

    update();

    if(spd == 0 && !isMoving)
        ptimer->stop();
}

int PathsView::getBlockYNum() {
    return (paths->size() + xNum - 1) / xNum;
}

void PathsView::updateChildPos() {
    int i = 0;
    for(auto it = paths->begin(); it < paths->end(); it++) {
        int btnX = i % xNum;
        int btnY = i / xNum;
        int toX = spacing + btnX * (PathBtn::bWidth + spacing);
        int toY = spacing + btnY * (PathBtn::bHeight + spacing);
        (*it)->move(toX, toY + offset);

        i++;
    }
}

void PathsView::sumSpdToOffset() {
    offset += spd;
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
bool PathsView::limitOffset(int minOffset) {
    if (offset > 0) {
        int limitSpd = 2 + (offset) / 4;
        offset -= limitSpd;
        if (offset < 0)
            offset = 0;
        return true;
    }
    if (offset < minOffset) {
        int limitSpd = 2 + (minOffset - offset) / 4;
        offset += limitSpd;
        if (offset > minOffset)
            offset = minOffset;
        return true;
    }
    return false;
}

void PathsView::wheelEvent(QWheelEvent *ev) {
    int num = ev->delta() / 20;
    if ((spd < 0 && num > 0) || (spd > 0 && num < 0))
        spd = 0;
    spd += num;
    if (abs(spd) > 8)
        spd > 0 ? spd = 20 : spd = -20;

    if(!ptimer->isActive())
        ptimer->start(16);
}


void PathsView::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor(200, 200, 200));


}
