#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QCoreApplication>

#include <QPainter>

#define SC static constexpr
#define APP_DIR QCoreApplication::applicationDirPath()


#define GET_VARIBLE_FUNC(FuncName, varibleName, varibleType)\
    varibleType get##FuncName(){return varibleName;}

#define SET_VARIBLE_FUNC(FuncName, varibleName, varibleType)\
    void set##FuncName(varibleType _inputvar_){varibleName = _inputvar_;}

#define VARIBLE_FUNC(FuncName, varibleName, varibleType)\
    GET_VARIBLE_FUNC(FuncName, varibleName, varibleType)\
    SET_VARIBLE_FUNC(FuncName, varibleName, varibleType)


inline void limitWidth(QWidget *widget, int w) {
    widget->setMinimumWidth(w);
    widget->setMaximumWidth(w);
}

inline void limitHeight(QWidget *widget, int h) {
    widget->setMinimumHeight(h);
    widget->setMaximumHeight(h);
}

inline void limitSize(QWidget *widget, int w, int h) {
    limitWidth(widget, w);
    limitHeight(widget, h);
}


inline void jDrawRecFrame(QPainter *p, int x, int y, int w, int h, int width, QColor c) {
    p->fillRect(x, y, w, width, c);
    p->fillRect(x, y, width, h, c);
    p->fillRect(x + w - width, y, width, h, c);
    p->fillRect(x, y + h - width, w, width, c);
}
inline void jDrawRecFrame(QPainter *p, QRect rect, int width, QColor c)
{jDrawRecFrame(p,rect.x(), rect.y(), rect.width(), rect.height(), width, c);}

#endif // HEADER_H
