#include "extensionitem.h"

ExtensionItem::ExtensionItem(LibManager libManager)
    : libManager(libManager) {}

void ExtensionItem::onPaint(QPainter &p, QRect r, ButtonFlag flag) {
    QRegion prevRegion = p.clipRegion();
    p.setClipRect(r);

    static constexpr QRgb baseColor = qRgb(116, 212, 116);
    switch(flag) {
    case ButtonFlag::None: p.fillRect(r, QColor(baseColor)); break;
    case ButtonFlag::MouseAt: p.fillRect(r, QColor(baseColor).lighter(115)); break;
    case ButtonFlag::MouseHolding: p.fillRect(r, QColor(baseColor).darker(115)); break;
    }

    if(libManager.libPixmap.isNull()) {
        p.drawText(r, Qt::AlignCenter | Qt::AlignVCenter, libManager.libName);
    } else {
        QPixmap& libPixmap = libManager.libPixmap;

        int totalHeight = libPixmap.height();

        static constexpr int spacing = 2;
        QFontMetrics fm(p.font());
        totalHeight += spacing + fm.height();

        int pixmapX = (r.width() - libPixmap.width()) / 2;
        int pixmapY = (r.height() - totalHeight) / 2;
        p.drawPixmap(r.x() + pixmapX, r.y() + pixmapY, libPixmap);

        int offset = pixmapY + libPixmap.height() + spacing;
        r.setY(r.y() + offset);
        r.setHeight(fm.height());

        p.drawText(r, Qt::AlignCenter | Qt::AlignTop, libManager.libName);
    }

    p.setClipRegion(prevRegion);
}
