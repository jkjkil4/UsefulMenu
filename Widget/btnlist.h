#ifndef BTNLIST_H
#define BTNLIST_H

#include <QWidget>

#include "Class/global.h"

class BtnList : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);

public:
    explicit BtnList(QWidget *parent = nullptr);

    void updateChildsPos();

    VARIBLE_FUNC(Start, start, int)
    VARIBLE_FUNC(Spacing, spacing, int)

    VARIBLE_FUNC(SuitableHeight, suitableHeight, int)

private:
    int start = 24;
    int spacing = 5;

    int suitableHeight = 10;
};

#endif // BTNLIST_H
