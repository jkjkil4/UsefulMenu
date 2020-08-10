#ifndef VERAREAPOINT_H
#define VERAREAPOINT_H

#include "areaparent.h"

class VerArea : public AreaParent
{
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    explicit VerArea(Type type, int *pY, int *pX1, int *pX2, QWidget *parent = nullptr);
    ~VerArea() override = default;

    void onMouseMoving(int y);

    void onOtherMoved() override;

    Type type;
    int *pY = nullptr, *pX1 = nullptr, *pX2 = nullptr;

private:
    int startY = 0;
};

#endif // VERAREAPOINT_H
