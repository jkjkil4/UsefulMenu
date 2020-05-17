#ifndef AREAPARENT_H
#define AREAPARENT_H

#include <QWidget>

#include "Class/global.h"

class AreaParent : public QWidget
{
    Q_OBJECT
public:
    explicit AreaParent(int *x, int *y, QWidget *parent = nullptr)
        : QWidget(parent), pX(x), pY(y){}
    ~AreaParent() override = default;

    virtual void onOtherMoved() {}

    int *pX = nullptr, *pY = nullptr;


signals:
    void moved();
    void released();
};

#endif // AREAPARENT_H
