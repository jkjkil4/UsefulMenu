#ifndef IMGVIEW_H
#define IMGVIEW_H

#include <QWidget>

#include "header.h"

class ImgView : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *) override;

public:
    explicit ImgView(QImage *img, QWidget *parent = nullptr);
    ~ImgView() override = default;

    VARIBLE_FUNC(FocusPos, focusPos, QPoint)

    //和绘制大图的相关的一些变量
    SC int pixelSize = 3;
    SC int pixelXNum = 41;
    SC int pixelYNum = 41;

    SC int infoViewHeight = 40;
    SC int borderWidth = 1;
    SC int offset = 20;

    SC int viewWidth = borderWidth * 2 + pixelSize * pixelXNum;
    SC int viewHeight = borderWidth * 2 + pixelSize * pixelYNum;

private:
    QImage *img = nullptr;

    QPoint focusPos;
};

#endif // IMGVIEW_H
