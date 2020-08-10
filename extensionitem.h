#ifndef EXTENSIONITEM_H
#define EXTENSIONITEM_H

#include "buttontable.h"

#include "libmanager.h"

#include <QFileInfo>

class ExtensionItem : public ButtonTableItem
{
public:
    ExtensionItem(LibManager libManager);

    void onPaint(QPainter& p, QRect r, ButtonFlag flag);

    LibManager libManager;
};

#endif // EXTENSIONITEM_H
