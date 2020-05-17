#ifndef SELECTAREA_H
#define SELECTAREA_H

#include <QWidget>

#include "Class/global.h"

class SelectArea : public QWidget
{
    Q_OBJECT
public:
    explicit SelectArea(QWidget *parent = nullptr);
    ~SelectArea() override = default;

    VARIBLE_FUNC(PointSize, pointSize, int)
    VARIBLE_FUNC(LineSize, lineSize, int)

private:
    int pointSize = 5;
    int lineSize = 2;

};

#endif // SELECTAREA_H
