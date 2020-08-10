#ifndef HORAREAPOINT_H
#define HORAREAPOINT_H

#include "areaparent.h"

class HorArea : public AreaParent
{
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    explicit HorArea(Type type, int *pX, int *pY1, int *pY2, QWidget *parent = nullptr);
    ~HorArea() override = default;

    void onMouseMoving(int x);

    void onOtherMoved() override;

    Type type;
    int *pX = nullptr, *pY1 = nullptr, *pY2 = nullptr;

private:
    int startX = 0;
};

#endif // HORAREAPOINT_H
