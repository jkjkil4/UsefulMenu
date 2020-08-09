#ifndef BUTTONTABLEITEM_H
#define BUTTONTABLEITEM_H

#include <QPainter>

class ButtonTableItem
{
public:
    virtual ~ButtonTableItem() = default;

    enum class ButtonFlag { None, MouseAt, MouseHolding };

    virtual void onPaint(QPainter& p, QRect r, ButtonFlag flag) {
        QColor dwColor;
        switch(flag) {
        case ButtonFlag::None:
            dwColor = QColor(96, 192, 96);
            break;
        case ButtonFlag::MouseAt:
            dwColor = QColor(96, 96, 192);
            break;
        case ButtonFlag::MouseHolding:
            dwColor = QColor(192, 96, 96);
            break;
        }
        p.fillRect(r, dwColor);
    }
};

#endif // BUTTONTABLEITEM_H
