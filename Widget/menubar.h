#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>

#include <QPainter>
#include <QHBoxLayout>
#include <QMouseEvent>

#include "iconbtn.h"

class MenuBar : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void paintEvent(QPaintEvent*) override;

public:
    explicit MenuBar(QWidget *parent = nullptr);

signals:
    void wndClose();
    void wndHide();
    void wndMoveOffset(int, int);

private:
    IconBtn* btnExit = new IconBtn(QIcon(":/MainWidgetBtn/Resource/Exit.png"));
    IconBtn* btnHide = new IconBtn(QIcon(":/MainWidgetBtn/Resource/min.png"));

    QPoint mousePosStart;
};

#endif // MENUBAR_H
