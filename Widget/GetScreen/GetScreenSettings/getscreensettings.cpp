#include "getscreensettings.h"

GetScreenSettings::GetScreenSettings(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "GetScreenSettings构造函数";
}

GetScreenSettings::~GetScreenSettings() {
    qDebug() << "GetScreenSettings析构函数";
}


void GetScreenSettings::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::darkGray);
}
