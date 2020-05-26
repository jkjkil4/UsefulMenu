#include "pathbtn.h"

#include <QDebug>

PathBtn::PathBtn(QString path, QWidget *parent)
    : QAbstractButton(parent),
      path(path)
{
    //得到文件名
    QFileInfo info(path);
    fileName = info.baseName();
    setToolTip(info.fileName());

    //得到图标
    pathIcon = QFileIconProvider().icon(path).pixmap(32, 32);

    //设置属性
    limitSize(this, bWidth, bHeight);

    //点击之后打开文件/文件夹
    connect(this, &PathBtn::clicked, [=]{
        qDebug() << fileName + "被点击";
    });
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

    //绘制图标
    p.drawPixmap((width() - pathIcon.width()) / 2,
                 borderSize + 3,
                 pathIcon);

    //绘制文字
    int drawX = width() / 2;
    int xLimit = width() - 2 * borderSize;
    p.setPen(Qt::white);
    jDrawText(&p, drawX, height() - borderSize - 3, Qt::AlignBottom, fileName, xLimit); //绘制文件名(底部)
}
