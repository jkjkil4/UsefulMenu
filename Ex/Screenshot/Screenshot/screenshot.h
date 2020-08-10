#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include "screenshot_global.h"

#include <QWidget>

#include <QSettings>

typedef void(QWidget::*ShowFunc)();

extern "C" {
    SCREENSHOTSHARED_EXPORT QWidget* newHandle();
    //SCREENSHOTSHARED_EXPORT void setShowFuncPtr(QWidget* funcWidget, ShowFunc func);
}

class Screenshot : public QWidget
{

public:
    Screenshot();
};

#endif // SCREENSHOT_H
