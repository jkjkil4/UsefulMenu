#ifndef AREAPARENT_H
#define AREAPARENT_H

#include <QWidget>

#include "Class/global.h"

class AreaParent : public QWidget
{
    Q_OBJECT
public:
    explicit AreaParent(QWidget *parent = nullptr)
        : QWidget(parent){}
    ~AreaParent() override = default;

    virtual void onOtherMoved() {}


signals:
    void moved();
    void released();
};

#endif // AREAPARENT_H
