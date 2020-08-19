#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>

#include <QPainter>

#include <QMouseEvent>
#include <QHBoxLayout>

#include "iconbtn.h"

class MenuBar : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    MenuBar(QWidget* parent = nullptr);

signals:
    void wndMoveOffset(int, int);

    void wndBack();
    void wndClose();

    void newItem();

private:
    QPoint mousePosStart;
};

#endif // MENUBAR_H
