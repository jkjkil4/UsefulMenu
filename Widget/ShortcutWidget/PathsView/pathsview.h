#ifndef PATHSVIEW_H
#define PATHSVIEW_H

#include <QWidget>

#include <QWheelEvent>
#include <QTimer>

#include "pathbtn.h"

class PathsView : public QWidget
{
    Q_OBJECT
protected:
    void wheelEvent(QWheelEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    explicit PathsView(QList<PathBtn*> *paths, QWidget *parent = nullptr);
    ~PathsView() override = default;

    int getBlockYNum();

    void updateChildPos();

    void sumSpdToOffset();
    bool limitOffset(int minOffset);

    //和大小相关的一些东西
    SC int spacing = 1;

    SC int xNum = 6;
    SC int totalWidth = spacing + xNum * (spacing + PathBtn::bWidth);

    SC int totalHeight = 240;

public slots:
    void slotTimer();

private:
    QList<PathBtn*> *paths = nullptr;

    int offset = 0;
    int spd = 0;

    QTimer *ptimer = new QTimer(this);
};

#endif // PATHSVIEW_H
