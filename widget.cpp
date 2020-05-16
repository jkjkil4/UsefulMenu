#include "widget.h"

#include <QGuiApplication>
#include <QScreen>

#include "Widget/ball.h"
#include "Widget/btnlist.h"

#include "Class/iconbtn.h"

#include "Class/global.h"

#include <QDebug>

#ifdef WIDGET_DEBUG
#include <QPainter>
#endif

Widget::Widget(QWidget *parent) : QWidget(parent) {
    //功能列表，
    btnList = new BtnList(this);
    limitWidth(btnList, 24);
    btnList->move((32 - btnList->width()) / 2, 16);
    //功能列表的按钮
    IconBtn *btnGetScreen = new IconBtn(btnList);
    btnGetScreen->setIcon(QIcon(":/funcBtn/Resource/cut.png"));
    limitSize(btnGetScreen, 20, 20);
    //
    IconBtn *btnShortcut = new IconBtn(btnList);
    btnShortcut->setIcon(QIcon(":/funcBtn/Resource/fast.png"));
    limitSize(btnShortcut, 20, 20);

    btnList->updateChildsPos();
    maxHeight = btnList->getSuitableHeight() + btnList->y();

    //球形区域，显示CPU和RAM使用率
    ball = new Ball(this);
    //信号与槽
    connect(ball, &Ball::wndShowNarrow, [=]{
        isMoving = true;
        showNarrow();
    });
    connect(ball, &Ball::wndShowExpand, [=]{
        isMoving = false;
        showExpand();
    });
    connect(ball, &Ball::wndMoveOffset, [=](int xOffset, int yOffset){
        int toX = x() + xOffset;
        int toY = y() + yOffset;
        QSize wndSize = QGuiApplication::primaryScreen()->availableSize();
        move(qBound(0, toX, wndSize.width() - width()),
             qBound(0, toY, wndSize.height() - height()));
    });
    connect(ball, &Ball::closeWidget, [=]{close();});

    //检测鼠标进入和离开
    connect(checkMouse, SIGNAL(timeout()), this, SLOT(onCheckMouse()));

    //设置为32x32
    showNarrow();
    //设置  窗口不显示在任务栏，无边框窗口，保持顶端
    setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //设置在窗口关闭时退出
    setAttribute(Qt::WA_QuitOnClose);
    //设置透明背景
    setAttribute(Qt::WA_TranslucentBackground);
    //不按下鼠标也可触发mouseMoveEvent
    setMouseTracking(true);
    ball->setMouseTracking(true);
}

Widget::~Widget() {

}


void Widget::showNarrow() {
    limitSize(this, 32, 32);
    btnList->setVisible(false);
}

void Widget::showExpand() {
    limitSize(this, 32, maxHeight);
    btnList->setVisible(true);
}

void Widget::onCheckMouse() {
    if(!isMoving && !QRect(0, 0, width(), height()).contains(mapFromGlobal(cursor().pos()))) {
        showNarrow();
        checkMouse->stop();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *) {
    if(!checkMouse->isActive()) {
        showExpand();
        checkMouse->start(16);
    }
}

#ifdef WIDGET_DEBUG
void Widget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
}
#endif
