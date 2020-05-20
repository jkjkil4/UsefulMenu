#ifndef LINE_H
#define LINE_H

#include <QWidget>

#include "Class/global.h"

class Line : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);

public:
    explicit Line(Qt::Orientation ori, QColor color = Qt::black, QWidget *parent = nullptr);

    VARIBLE_FUNC(Color, color, QColor)

private:
    QColor color;
};

#endif // LINE_H
