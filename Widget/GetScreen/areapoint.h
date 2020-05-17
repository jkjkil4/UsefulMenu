#ifndef AREAPOINT_H
#define AREAPOINT_H

#include "areaparent.h"

class AreaPoint : public AreaParent
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    explicit AreaPoint(int *x, int *y, QWidget *parent = nullptr);
    ~AreaPoint() override = default;

    void onOtherMoved() override;

private:
    QPoint startPos;
};

#endif // AREAPOINT_H
