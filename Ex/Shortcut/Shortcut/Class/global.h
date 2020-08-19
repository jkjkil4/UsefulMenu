#ifndef SHOWFUNC_H
#define SHOWFUNC_H

#include <QWidget>

class ShortcutWidget;

typedef void(QWidget::*ShowFunc)();

extern QWidget *funcWidget;
extern ShowFunc func;

extern ShortcutWidget *curShortcutWidget;


#endif // SHOWFUNC_H
