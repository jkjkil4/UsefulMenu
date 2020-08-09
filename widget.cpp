#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(btnTable);
    setLayout(layout);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    resize(800, 608);
}

void Widget::paintEvent(QPaintEvent *){
    //QPainter(this).fillRect(rect(), QColor(102, 204, 255, 128));
    QPainter p(this);
    jDrawRecFrame(p, 0, 0, width(), height(), layout()->margin(), QColor(102, 204, 255, 200));
}
