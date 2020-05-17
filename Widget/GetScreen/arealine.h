#ifndef AREALINE_H
#define AREALINE_H

#include <QWidget>
#include "areaparent.h"

class AreaLine : public AreaParent
{
    Q_OBJECT
public:
    explicit AreaLine(int *x, int *y, QWidget *parent = nullptr);
    ~AreaLine() override = default;

    void onOtherMoved() override;
};

#endif // AREALINE_H