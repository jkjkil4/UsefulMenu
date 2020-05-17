#ifndef HORAREALINE_H
#define HORAREALINE_H

#include "horarea.h"

class HorAreaLine : public HorArea
{
public:
    explicit HorAreaLine(int *pX, int *pY1, int *pY2, QWidget *parent = nullptr);
    ~HorAreaLine() override = default;

    void onInit() override;

    void onOtherMoved() override;
};

#endif // HORAREALINE_H
