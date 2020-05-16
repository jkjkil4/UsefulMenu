#include "iconbtn.h"

#include <QPainter>
#include <QDebug>

IconBtn::IconBtn(QWidget *parent) : QAbstractButton(parent) {

}

bool IconBtn::checkMouseAt() {
    QPoint mouse = mapFromGlobal(cursor().pos());
    return QRect(0, 0, width(), height()).contains(mouse);
}


void IconBtn::paintEvent(QPaintEvent *) {
    bool mouseAt = checkMouseAt();
    bool down = isDown();

    QPainter p(this);

    QColor color;
    if(down) {
        color = colorHolding;
    }
    else if(mouseAt) {
        color = colorMouseAt;
    }
    else {
        color = colorNormal;
    }

    p.fillRect(2, 2, width() - 4, height() - 4, color);
    QSize size = iconSize();
    p.drawPixmap((width() - size.width()) / 2, (height() - size.height()) / 2, icon().pixmap(size));
    jDrawRecFrame(&p, 0, 0, width(), height(), 2, color.darker(120));
}
