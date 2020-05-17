#include "getscreen.h"

#include "arealine.h"
#include "areapoint.h"

GetScreen::GetScreen(QImage *img)
    : img(img)
{
    //左上角
    areaPoints.push_back(new AreaPoint(&area.x1, &area.y1, this));
    //右上角
    areaPoints.push_back(new AreaPoint(&area.x2, &area.y1, this));
    //左下角
    areaPoints.push_back(new AreaPoint(&area.x1, &area.y2, this));
    //右下角
    areaPoints.push_back(new AreaPoint(&area.x2, &area.y2, this));

    for(auto controler : areaPoints) {
        connect(controler, SIGNAL(moved()), this, SLOT(onAreaChanged()));
        connect(controler, SIGNAL(released()), this, SLOT(onAreaChangeDone()));
    }

    changeArea->setSingleShot(true);
    connect(changeArea, SIGNAL(timeout()), this, SLOT(onChangeAreaTimeout()));

    //设置窗口属性
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SubWindow | Qt::FramelessWindowHint);
    //全屏
    showFullScreen();
    //设置大小
    resize(img->size());
    move(0, 0);
}

GetScreen::~GetScreen() {
    for(auto controler : areaPoints)
        delete controler;
}


QCursor GetScreen::getCursorType(int flags) {
    int x = (flags & Qt::AlignLeft ? 0 : (flags & Qt::AlignRight ? 2 : 1));
    int y = (flags & Qt::AlignTop ? 0 : (flags & Qt::AlignBottom ? 2 : 1));
    return alignMap[x][y];
}


void GetScreen::onAreaChanged() {
    ((AreaParent*)sender())->onOtherMoved();
    if(!changeArea->isActive())
        changeArea->start(16);
}
void GetScreen::onChangeAreaTimeout() {
    for(auto point : areaPoints)
        point->onOtherMoved();
}

void GetScreen::onAreaChangeDone() {
    int *left = (area.x1 < area.x2 ? &area.x1 : &area.x2);
    int *top = (area.y1 < area.y2 ? &area.y1 : &area.y2);
    QPoint leftTop(qMin(area.x1, area.x2), qMin(area.y1, area.y2));
    QPoint rightBottom(qMax(area.x1, area.x2), qMax(area.y1, area.y2));
    for(auto point : areaPoints) {
        int flags = (point->pX == left ? Qt::AlignLeft : Qt::AlignRight);
        flags |= (point->pY == top ? Qt::AlignTop : Qt::AlignBottom);
        point->setCursor(getCursorType(flags));
    }
}


void GetScreen::setControlerVisible(bool on) {
    for(auto controler : areaPoints)
        controler->setVisible(on);
}


void GetScreen::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.drawImage(0, 0, *img);

    p.setBrush(QColor(0, 0, 0, 128));
    p.drawRect(0, 0, width(), height());
}
