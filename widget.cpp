#include "widget.h"

#include "ball.h"

#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    new Ball(this);
}

Widget::~Widget() {

}


void Widget::focusOutEvent(QFocusEvent *) {
    qDebug() << "widget focus out";
}
