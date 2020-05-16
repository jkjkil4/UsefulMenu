#ifndef ICONBTN_H
#define ICONBTN_H

#include <QAbstractButton>

#include "global.h"

class IconBtn : public QAbstractButton
{
protected:
    void paintEvent(QPaintEvent *);

public:
    explicit IconBtn(QWidget *parent = nullptr);

    VARIBLE_FUNC(Icon, icon, QIcon)

private:
    QIcon icon;
};

#endif // ICONBTN_H
