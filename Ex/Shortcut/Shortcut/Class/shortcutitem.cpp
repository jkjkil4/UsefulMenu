#include "shortcutitem.h"

ShortcutItem::ShortcutItem(const QString& filePath) : filePath(filePath)
{
    pix = QFileIconProvider().icon(filePath).pixmap(32, 32);
    fileName = QFileInfo(filePath).fileName();
    fileName = fileName.left(fileName.lastIndexOf('.'));
}

void ShortcutItem::onPaint(QPainter &p, QRect r, ButtonFlag flag) {
    static QColor baseColor = QColor(210, 190, 90);
    switch(flag) {
    case ButtonFlag::MouseHolding: p.fillRect(r, baseColor.darker(115)); break;
    case ButtonFlag::MouseAt: p.fillRect(r, baseColor.lighter(115)); break;
    case ButtonFlag::None: p.fillRect(r, baseColor); break;
    }

    static constexpr int spacing = 4;
    int totalHeight = pix.height() + spacing;
    QFontMetrics fm(p.font());
    totalHeight += fm.height();

    int pixX = (r.width() - pix.width()) / 2;
    int pixY = (r.height() - totalHeight) / 2;
    p.drawPixmap(r.x() + pixX, r.y() + pixY, pix);

    r.setY(r.y() + pixY + pix.height() + spacing);
    r.setHeight(fm.height());

    p.drawText(r, Qt::AlignCenter | Qt::AlignTop, fileName);
}

QString ShortcutItem::tooltipText() {
    return QFileInfo(filePath).fileName();
}
