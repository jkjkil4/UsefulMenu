#ifndef HEADER_H
#define HEADER_H

#include <QWidget>

#define SC static constexpr


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

#endif // HEADER_H
