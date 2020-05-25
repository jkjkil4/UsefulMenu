#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>

#include <QPainter>

#define VARIBLE_FUNC(FuncName, varibleName, varibleType)\
    varibleType get##FuncName(){return varibleName;}\
    void set##FuncName(varibleType _inputvar_){varibleName = _inputvar_;}

#define SC static constexpr

//#define TIME_DEBUG
#ifdef TIME_DEBUG
# include <QTime>
# define TIME_BEGIN QTime _t_;_t_.start();
# define TIME_OUTPUT(str) qDebug().noquote() << str << _t_.elapsed()
# define TIME_RESTART _t_.restart();
#endif

template<typename T>inline void safeDelete(T *&p) {
    if(p) {
        delete p;
        p = nullptr;
    }
}


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



inline void jDrawText(QPainter *p, int x, int y, int flags, QString str, int xLimit = -1, int yLimit = -1){
    //字体
    QFontMetrics fm(p->font());
    QRect rec = fm.boundingRect(QRect(0,0,INT_MAX,INT_MAX),Qt::TextFlag(),str);
    //大小
    int w=rec.width(),h=rec.height();
    if( xLimit != -1 && w > xLimit )
        w = xLimit;
    if( yLimit != -1 && h > yLimit )
        h = yLimit;
    //判断
    x -= w/2;
    y -= h/2;
    if( flags & Qt::AlignRight )
        x -= w/2;
    if( flags & Qt::AlignLeft )
        x += w/2;
    if( flags & Qt::AlignBottom )
        y -= h/2;
    if( flags & Qt::AlignTop )
        y += h/2;
    //字符串所占的像素宽度,高度
    QRect r=QRect( x,y,w,h );
    //绘制
    //fillRect(r,QColor(255,255,0));  //这是调试用的
    p->drawText(r,flags,str);
}
inline void jDrawText(QPainter *p, QPoint pos, int flags, QString str, int xLimit = -1, int yLimit = -1){jDrawText(p,pos.x(),pos.y(),flags,str,xLimit,yLimit);}


#endif // GLOBAL_H
