#ifndef SHORTCUTITEM_H
#define SHORTCUTITEM_H

#include "buttontable.h"

#include <QFileInfo>
#include <QFileIconProvider>


class ShortcutItem : public ButtonTableItem
{
public:
    ShortcutItem(const QString& filePath);

    void onPaint(QPainter &p, QRect r, ButtonFlag flag) override;
    QString tooltipText() override;

    QPixmap pix;
    QString fileName;
    QString filePath;
};

#endif // SHORTCUTITEM_H
