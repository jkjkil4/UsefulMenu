#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <QPainter>

#include <QDebug>

#define SC static constexpr

#define repeat(v, n) for(int v = 0; v < n; v++)

//#define MOD(a, b) a >= 0 ? a % b : -(-a % b)

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

#endif // NAMESPACE_H
