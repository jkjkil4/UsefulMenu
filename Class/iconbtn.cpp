#include "iconbtn.h"

#include <QPainter>
#include <QDebug>

IconBtn::IconBtn(QWidget *parent) : QAbstractButton(parent) {

}


void IconBtn::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::blue);
}
