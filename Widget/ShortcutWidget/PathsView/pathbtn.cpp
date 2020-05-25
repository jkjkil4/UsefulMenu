#include "pathbtn.h"

PathBtn::PathBtn(QString path, QWidget *parent)
    : QAbstractButton(parent),
      path(path)
{
    limitSize(this, bWidth, bHeight);
}

bool PathBtn::isMouseAt() {
    return QRect(0, 0, width(), height())
            .contains(mapFromGlobal(cursor().pos()));
}

void PathBtn::paintEvent(QPaintEvent *) {
    QPainter p(this);

    if(isMouseAt())
        jDrawRecFrame(&p, 0, 0, width(), height(), borderSize, colBorder);

    QColor color = colNormal;
    if(isDown())
        color = colHolding;

    p.fillRect(borderSize, borderSize, width() - 2 * borderSize, height() - 2 * borderSize, color);
}
