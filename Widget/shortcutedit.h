#ifndef SHORTCUTEDIT_H
#define SHORTCUTEDIT_H

#include <QWidget>

#include <QKeyEvent>
#include <QPainter>

#include "namespace.h"

#include <qxtglobalshortcut.h>

#include <QDebug>

class ShortcutEdit : public QWidget
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent* ev) override;
    void paintEvent(QPaintEvent*) override;

public:
    explicit ShortcutEdit(QxtGlobalShortcut* shortcut, QWidget *parent = nullptr);
    ~ShortcutEdit() override;

    QxtGlobalShortcut* shortcut;
    QFont font;
};

#endif // SHORTCUTEDIT_H
