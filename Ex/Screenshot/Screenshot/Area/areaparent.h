#ifndef AREAPARENT_H
#define AREAPARENT_H

#include <QWidget>

#include "header.h"

class AreaParent : public QWidget
{
    Q_OBJECT
public:
    enum Type {Point, Line};

    explicit AreaParent(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setMouseTracking(true);
    }

    ~AreaParent() override = default;

    virtual void onOtherMoved() {}

    SC int pointSize = 5;
    SC int pointRadius = pointSize / 2;

signals:
    void moved();
    void released();
};

#endif // AREAPARENT_H
