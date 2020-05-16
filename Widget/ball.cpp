#include "ball.h"

#include <QPainter>
#include <QMenu>
#include <QAction>

#include <JQCPUMonitor>

#include "Class/rammonitor.h"
#include "Class/global.h"

#include <QDebug>

Ball::Ball(QWidget *parent) : QWidget(parent) {
    //限制大小
    limitSize(this, 32, 32);
    setCursor(Qt::PointingHandCursor);

    //初始化JQCPUMonitor
    JQCPUMonitor::initialize();

    //开始定时器
    checkUsage->start(1000);
    connect(checkUsage, SIGNAL(timeout()), this, SLOT(onCheckUsage()));
}

void Ball::onCheckUsage() {
    //得到CPU使用率
    cpuUsage = JQCPUMonitor::cpuUsagePercentage();
    cpuArc = static_cast<int>(cpuUsage * 2880);

    //得到内存使用率
    ramUsage = getRAMUsage();
    ramArc = static_cast<int>(ramUsage * 2880);

    //更新
    update();
}

void Ball::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        mousePosStart = ev->pos();
        emit wndShowNarrow();
    }
}

void Ball::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        QPoint mousePos = ev->pos();
        int xOffset = mousePos.x() - mousePosStart.x();
        int yOffset = mousePos.y() - mousePosStart.y();
        emit wndMoveOffset(xOffset, yOffset);
    }
    ev->ignore();
}

void Ball::mouseReleaseEvent(QMouseEvent *ev) {
    switch((int)ev->button()) {
    case Qt::LeftButton:
        emit wndShowExpand();
        break;
    case Qt::RightButton:{
        QAction actExit("退出");

        QMenu menu;
        menu.addAction(&actExit);

        menu.move(cursor().pos());
        QAction *res = menu.exec();

        if(res == &actExit) {
            emit closeWidget();
        }

        break;
    }
    }
}

void Ball::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    //绘制圆
    p.setBrush(QColor(230,230,230));
    p.setPen(QColor(190,190,190));
    p.drawEllipse(1,1,30,30);

    //绘制圆弧
      //CPU
    p.setPen(QPen(QColor(100,100,255),3));
    p.setClipRect(0,0,15,32);
    p.drawArc(5,5,22,22,4320,-cpuArc);
      //CPU-Gray
    p.setPen(QPen(QColor(200,200,200),3));
    p.drawArc(5,5,22,22,1440,2880-cpuArc);
      //RAM
    p.setPen(QPen(QColor(255,100,255),3));
    p.setClipRect(17,0,15,32);
    p.drawArc(5,5,22,22,-1440,ramArc);
      //RAM-Gray
    p.setPen(QPen(QColor(200,200,200),3));
    p.drawArc(5,5,22,22,1440,ramArc-2880);
}
