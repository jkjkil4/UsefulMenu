#ifndef SHORTCUT_H
#define SHORTCUT_H

#include "shortcut_global.h"
#include "Widget/shortcutwidget.h"

#include <QGuiApplication>
#include <QScreen>

extern "C" {
    SHORTCUTSHARED_EXPORT QString getLibName();
    SHORTCUTSHARED_EXPORT QPixmap getLibPixmap();

    SHORTCUTSHARED_EXPORT void Main(QWidget *widget);

    SHORTCUTSHARED_EXPORT void setShowFuncPtr(QWidget *funcWidget, ShowFunc func);
}


inline QString getFileName(const QString filePath) {
    QString name = QFileInfo(filePath).fileName();
    return name.left(name.lastIndexOf('.'));
}


#endif // SHORTCUT_H
