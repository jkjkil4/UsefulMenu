#include "imgview.h"


#include <QMouseEvent>

ImgView::ImgView(QImage *img, QWidget *parent)
    : QWidget(parent),
      img(img)
{
    limitSize(this, viewWidth, viewHeight + infoViewHeight);
    setFixedWidth(viewWidth);
    setFixedHeight(viewHeight + infoViewHeight);

    setMouseTracking(true);
}


void ImgView::paintEvent(QPaintEvent *) {
    QPainter p(this);

    //绘制上半部分
    {
        //填充背景
        p.fillRect(borderWidth, borderWidth,
            viewWidth - 2 * borderWidth, viewHeight - 2 * borderWidth, Qt::black);

        //绘制大图
        QRect targetRect = QRect(borderWidth, borderWidth, viewWidth - 2 * borderWidth, viewHeight - 2 * borderWidth);
        QRect sourceRect = QRect(focusPos.x() - pixelXNum / 2, focusPos.y() - pixelYNum / 2, pixelXNum, pixelYNum);
        p.drawImage(targetRect, *img, sourceRect);

        //绘制边框
        jDrawRecFrame(&p, 0, 0, viewWidth, viewHeight, borderWidth, QColor(0, 180, 0));

        //绘制中间的横竖线
        p.setBrush(QColor(0, 180, 0, 140));
        p.setPen(Qt::NoPen);
        p.drawRect(borderWidth, borderWidth + pixelYNum / 2 * pixelSize,
                   viewWidth - 2 * borderWidth, pixelSize);   //横线
        p.drawRect(borderWidth + pixelXNum / 2 * pixelSize, borderWidth,
                   pixelSize, viewHeight - 2 * borderWidth);    //竖线
    }

    //绘制下半部分
    {
        QRect rect = QRect(0, viewHeight, viewWidth, infoViewHeight);

        //填充背景
        p.fillRect(rect, QColor(0, 0, 0, 180));

        //绘制像素信息
        p.setPen(QColor(255,255,255));
        QColor pixelColor = img->pixelColor(focusPos);
        p.drawText(rect, Qt::AlignCenter | Qt::AlignVCenter,
                   "POS:(" + QString::number(focusPos.x()) + ", " + QString::number(focusPos.y()) +
                   ")\nRGB:(" + QString::number(pixelColor.red()) + ", " + QString::number(pixelColor.green()) +
                   ", " + QString::number(pixelColor.blue()) + ")");
    }
}
