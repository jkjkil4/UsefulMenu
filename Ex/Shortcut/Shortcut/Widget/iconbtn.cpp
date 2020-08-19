#include "iconbtn.h"

#include <QPainter>
#include <QDebug>

IconBtn::IconBtn(QWidget *parent)
    : QAbstractButton(parent)
{
    limitSize(this, 24, 24);
}

IconBtn::IconBtn(QIcon icon, QWidget *parent)
    : QAbstractButton(parent)
{
    limitSize(this, 24, 24);
    setIcon(icon);
}

bool IconBtn::checkMouseAt() {
    QPoint mouse = mapFromGlobal(cursor().pos());
    return QRect(0, 0, width(), height()).contains(mouse);
}


void IconBtn::paintEvent(QPaintEvent *) {
    bool mouseAt = checkMouseAt();
    bool down = isDown();

    QPainter p(this);

    QColor color = bgColor;
    if(down) {
        color = color.darker(115);
    }
    else if(mouseAt) {
        color = color.lighter(115);
    }

    p.fillRect(0, 0, width(), height(), color);
    QSize size = iconSize();
    p.drawPixmap((width() - size.width()) / 2, (height() - size.height()) / 2, icon().pixmap(size));
}
