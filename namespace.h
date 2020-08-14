#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <QWidget>
#include <QPainter>
#include <QLibrary>
#include <QFileInfo>

#include <QDebug>

#define SC static constexpr

#define repeat(v, n) for(int v = 0; v < n; v++)

//#define MOD(a, b) a >= 0 ? a % b : -(-a % b)

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

inline void jDrawRecFrame(QPainter& p, int x, int y, int w, int h, int width, QColor c){
    //顶部
    p.fillRect(x, y, w, width, c);
    //左侧
    p.fillRect(x, y + width, width, h - 2 * width, c);
    //右侧
    p.fillRect(x + w - width, y + width, width, h - 2 * width, c);
    //底部
    p.fillRect(x, y + h - width, w, width, c);
}

inline QString getLibFileName(QLibrary* lib) {
    QString libName = QFileInfo(lib->fileName()).fileName();
    return libName.left(libName.lastIndexOf('.'));
}

inline int getLibOrder(const QMap<QString, int> &map, QLibrary *lib) {
    auto iter = map.find(getLibFileName(lib));
    if(iter == map.end())
        return 0;

    return *iter;
}

#endif // NAMESPACE_H
