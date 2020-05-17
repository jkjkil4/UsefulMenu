#include "getscreen.h"

#include "Area/areapoint.h"
#include "Area/horarea.h"
#include "Area/verarea.h"

#include <QDebug>

GetScreen::GetScreen(QImage *img)
    : img(img)
{
    //左侧的点
    areaWidgets.push_back(new HorArea(HorArea::Point, &area.x1, &area.y1, &area.y2, this));
    //右侧的点
    areaWidgets.push_back(new HorArea(HorArea::Point, &area.x2, &area.y1, &area.y2, this));
    //上方的点
    areaWidgets.push_back(new VerArea(VerArea::Point, &area.y1, &area.x1, &area.x2, this));
    //下方的点
    areaWidgets.push_back(new VerArea(VerArea::Point, &area.y2, &area.x1, &area.x2, this));

    //左侧的线
    areaWidgets.push_back(new HorArea(HorArea::Line, &area.x1, &area.y1, &area.y2, this));
    //右侧的线
    areaWidgets.push_back(new HorArea(HorArea::Line, &area.x2, &area.y1, &area.y2, this));
    //上方的线
    areaWidgets.push_back(new VerArea(VerArea::Line, &area.y1, &area.x1, &area.x2, this));
    //下方的线
    areaWidgets.push_back(new VerArea(VerArea::Line, &area.y2, &area.x1, &area.x2, this));

    //左上角
    areaPoints.push_back(new AreaPoint(&area.x1, &area.y1, this));
    //右上角
    areaPoints.push_back(new AreaPoint(&area.x2, &area.y1, this));
    //左下角
    areaPoints.push_back(new AreaPoint(&area.x1, &area.y2, this));
    //右下角
    areaPoints.push_back(new AreaPoint(&area.x2, &area.y2, this));

    for(auto point : areaPoints)
        areaWidgets.push_back(point);

    for(auto controler : areaWidgets) {
        connect(controler, SIGNAL(moved()), this, SLOT(onAreaChanged()));
        connect(controler, SIGNAL(released()), this, SLOT(onAreaChangeDone()));
    }
    onAreaChanged();

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
    for(auto controler : areaWidgets)
        delete controler;
}


QCursor GetScreen::getCursorType(int flags) {
    int x = (flags & Qt::AlignLeft ? 0 : (flags & Qt::AlignRight ? 2 : 1));
    int y = (flags & Qt::AlignTop ? 0 : (flags & Qt::AlignBottom ? 2 : 1));
    return alignMap[x][y];
}


void GetScreen::onAreaChanged() {
//    area.x1 = qBound(0, area.x1, img->width());
//    area.x2 = qBound(0, area.x2, img->width());
//    area.y1 = qBound(0, area.y1, img->height());
//    area.y2 = qBound(0, area.y2, img->height());

    AreaParent *pSender = (AreaParent*)sender();
    if(pSender)
        pSender->onOtherMoved();
    if(!changeArea->isActive())
        changeArea->start(18);
}
void GetScreen::onChangeAreaTimeout() {
    for(auto point : areaWidgets)
        point->onOtherMoved();

    cutRect = QRect(QPoint(area.x1, area.y1), QPoint(area.x2, area.y2)).normalized();

    update();
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
    for(auto controler : areaWidgets)
        controler->setVisible(on);
}


void GetScreen::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.drawImage(0, 0, *img);

    p.setPen(QColor(0, 0, 0, 0));
    p.setBrush(QColor(0, 0, 0, 128));

    QRegion region = QRegion(0, 0, width(), height()) - cutRect;

    for(auto rect : region)
        p.drawRect(rect);
}
