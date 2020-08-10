#include "extensionitem.h"

ExtensionItem::ExtensionItem(LibManager libManager)
    : libManager(libManager) {}
#include <QDebug>
void ExtensionItem::onPaint(QPainter &p, QRect r, ButtonFlag flag) {
    ButtonTableItem::onPaint(p, r, flag);

    QRegion prevRegion = p.clipRegion();
    p.setClipRect(r);

    if(libManager.libPixmap.isNull()) {
        p.drawText(r, Qt::AlignCenter | Qt::AlignVCenter, libManager.libName);
    } else {
        QPixmap& libPixmap = libManager.libPixmap;

        int totalHeight = libPixmap.height();

        QFontMetrics fm(p.font());
        totalHeight += fm.height();

        int pixmapX = (r.width() - libPixmap.width()) / 2;
        int pixmapY = (r.height() - totalHeight) / 2;
        p.drawPixmap(r.x() + pixmapX, r.y() + pixmapY, libPixmap);

        int offset = pixmapY + libPixmap.height();
        qDebug() << r;
        r.setY(r.y() + offset);
        r.setHeight(fm.height());
        qDebug() << r << "\n";

        p.drawText(r, Qt::AlignCenter | Qt::AlignTop, libManager.libName);
    }

    p.setClipRegion(prevRegion);
}
