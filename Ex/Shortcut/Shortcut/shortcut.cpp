#include "shortcut.h"


QString getLibName() {
    return "快捷方式";
}

QPixmap getLibPixmap() {
    return QPixmap(":/Shortcut/Resource/Shortcut.png");
}



void Main(QWidget *widget) {
    if(curShortcutWidget) {
        curShortcutWidget->close();
        curShortcutWidget = nullptr;
    }
    curShortcutWidget = new ShortcutWidget;
    curShortcutWidget->move(widget->pos());
    curShortcutWidget->show();
}


void setShowFuncPtr(QWidget *funcWidget, ShowFunc func) {
    ::funcWidget = funcWidget;
    ::func = func;
}

