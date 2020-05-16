#include "widget.h"

#include <QGuiApplication>
#include <QScreen>

#include "Widget/ball.h"
#include "Widget/btnlist.h"
#include "Class/global.h"

#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    //设置为32x32
    showNarrow();
    //设置  窗口不显示在任务栏，无边框窗口，保持顶端
    setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //设置在窗口关闭时退出
    setAttribute(Qt::WA_QuitOnClose);
    //设置透明背景
    setAttribute(Qt::WA_TranslucentBackground);

    //球形区域，显示CPU和RAM使用率
    ball = new Ball(this);

    connect(ball, &Ball::wndShowNarrow, [=]{
        showNarrow();
    });
    connect(ball, &Ball::wndShowExpand, [=]{
        showExpand();
    });
    connect(ball, &Ball::wndMoveOffset, [=](int xOffset, int yOffset){
        int toX = x() + xOffset;
        int toY = y() + yOffset;
        QSize wndSize = QGuiApplication::screens()[0]->availableSize();
        move(qBound(0, toX, wndSize.width() - width()),
             qBound(0, toY, wndSize.height() - height()));
    });
    connect(ball, &Ball::closeWidget, [=]{
        close();
    });

    //功能列表，
    //btnList = new BtnList;

}

Widget::~Widget() {

}


void Widget::showNarrow() {
    limitSize(this, 32, 32);
}

void Widget::showExpand() {

}
