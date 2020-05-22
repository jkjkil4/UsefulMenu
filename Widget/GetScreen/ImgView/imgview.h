#ifndef IMGVIEW_H
#define IMGVIEW_H

#include <QWidget>

#include "Class/global.h"

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
    static constexpr int pixelSize = 3;
    static constexpr int pixelXNum = 41;
    static constexpr int pixelYNum = 41;

    static constexpr int infoViewHeight = 40;
    static constexpr int borderWidth = 1;
    static constexpr int offset = 20;

    static constexpr int viewWidth = borderWidth * 2 + pixelSize * pixelXNum;
    static constexpr int viewHeight = borderWidth * 2 + pixelSize * pixelYNum;

private:
    QImage *img = nullptr;

    QPoint focusPos;
};

#endif // IMGVIEW_H
