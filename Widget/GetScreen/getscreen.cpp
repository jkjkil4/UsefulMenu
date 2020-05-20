#include "getscreen.h"

#include "Area/areapoint.h"
#include "Area/horarea.h"
#include "Area/verarea.h"

#include "ButtonMenu/buttonmenu.h"

#include "Class/iconbtn.h"
#include "Class/line.h"

#include <QMouseEvent>
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
        controler->setVisible(false);
        connect(controler, SIGNAL(moved()), this, SLOT(onAreaChanged()));
        connect(controler, SIGNAL(released()), this, SLOT(onAreaChangeDone()));
    }
    onAreaChanged();

    changeArea->setSingleShot(true);
    connect(changeArea, SIGNAL(timeout()), this, SLOT(onChangeAreaTimeout()));

    //按钮菜单
    btnMenu = new ButtonMenu(this);
    btnMenu->setBgColor(QColor(230, 230, 230));
    btnMenu->setMargin(5);
    btnMenu->setSpcing(3);
    btnMenu->addWidget(new IconBtn(QIcon(":/getScreenBtn/Resource/save1.png")));
    btnMenu->addWidget(new IconBtn(QIcon(":/getScreenBtn/Resource/save2.png")));
    btnMenu->addWidget(new Line(Qt::Vertical));
    btnMenu->addWidget(new IconBtn(QIcon(":/getScreenBtn/Resource/cancel.png")));
    btnMenu->addWidget(new IconBtn(QIcon(":/getScreenBtn/Resource/accept.png")));
    //btnMenu->adjustSize();

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
    area.x1 = qBound(0, area.x1, img->width() - 1);
    area.x2 = qBound(0, area.x2, img->width() - 1);
    area.y1 = qBound(0, area.y1, img->height() - 1);
    area.y2 = qBound(0, area.y2, img->height() - 1);

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


void GetScreen::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        if(isFirstMove) {
            QPoint pos = ev->pos();
            //这是区域的位置
            area.x1 = pos.x();
            area.y1 = pos.y();
            area.x2 = pos.x();
            area.y2 = pos.y();
            //显示
            onAreaChanged();
            onAreaChangeDone();
            setControlerVisible(true);
        }
    }
}

void GetScreen::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        if(isFirstMove) {
            QPoint pos = ev->pos();
            area.x2 = pos.x();
            area.y2 = pos.y();
            onAreaChanged();
        }
    }
}

void GetScreen::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        isFirstMove = false;
    }
}


void GetScreen::paintEvent(QPaintEvent *ev) {
    QPainter p(this);
    p.drawImage(0, 0, *img);

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 128));

    QRegion region = QRegion(0, 0, width(), height()) - cutRect;

    for(auto rect : region)
        p.drawRect(rect);

    QDialog::paintEvent(ev);
}
