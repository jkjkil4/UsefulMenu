#include "buttonmenu.h"

#include <QApplication>
#include <QScreen>

ButtonMenu::ButtonMenu(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout;
    setLayout(layout);

    setVisible(false);
}


void ButtonMenu::addWidget(QWidget *w) {
    layout->addWidget(w);
}

void ButtonMenu::setMargin(int margin) {
    layout->setMargin(margin);
}

void ButtonMenu::setSpcing(int spacing) {
    layout->setSpacing(spacing);
}


void ButtonMenu::myShow(QPoint pos) {
    //屏幕高度
    int screenHeight = QApplication::primaryScreen()->size().height();

    int toX = pos.x() - width() - 1;        //将要设置的横坐标
    int toY = pos.y() + areaSpacing;    //将要设置的纵坐标

    //对toX和toY进行限制
    if(toX < 0)
        toX = 0;
    if(toY + height() > screenHeight)
        toY -= height() + areaSpacing * 2;

    //移动和显示
    move(toX, toY);
    setVisible(true);
}

void ButtonMenu::myHide() {
    setVisible(false);
}


void ButtonMenu::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(1, 1, width(), height(), bgColor);
    jDrawRecFrame(&p, 0, 0, width(), height(), 1, bgColor.darker(140));
}
