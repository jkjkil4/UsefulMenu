#ifndef BUTTONMENU_H
#define BUTTONMENU_H

#include <QWidget>
#include <QHBoxLayout>

#include "Class/global.h"

class ButtonMenu : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);

public:
    explicit ButtonMenu(QWidget *parent = nullptr);

    void addWidget(QWidget *w);
    void setMargin(int margin);
    void setSpcing(int spacing);

    VARIBLE_FUNC(BgColor, bgColor, QColor)

private:
    QHBoxLayout *layout = nullptr;
    QColor bgColor = Qt::lightGray;
};

#endif // BUTTONMENU_H
