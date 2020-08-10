#include "extensionitem.h"

ExtensionItem::ExtensionItem(LibManager libManager)
    : libManager(libManager) {}

void ExtensionItem::onPaint(QPainter &p, QRect r, ButtonFlag flag) {
    ButtonTableItem::onPaint(p, r, flag);
    p.drawText(r, Qt::AlignCenter | Qt::AlignVCenter, QFileInfo(libManager.lib->fileName()).fileName());
}
