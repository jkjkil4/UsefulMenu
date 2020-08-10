#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(btnTable);
    setLayout(layout);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    adjustSize();
    resize(width(), 608);
}

void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    jDrawRecFrame(p, 0, 0, width(), height(), layout()->margin(), QColor(102, 204, 255, 200));
}

