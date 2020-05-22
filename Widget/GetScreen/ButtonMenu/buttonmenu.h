#ifndef BUTTONMENU_H
#define BUTTONMENU_H

#include <QWidget>
#include <QHBoxLayout>

#include "Class/global.h"

class ButtonMenu : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *) override;

public:
    explicit ButtonMenu(QWidget *parent = nullptr);
    ~ButtonMenu() override = default;

    void addWidget(QWidget *w); //添加控件
    void setMargin(int margin); //设置边缘空隙
    void setSpcing(int spacing);//设置控件空隙

    void myShow(QPoint pos);    //显示
    void myHide();              //隐藏

    VARIBLE_FUNC(BgColor, bgColor, QColor)
    VARIBLE_FUNC(AreaSpacing, areaSpacing, int)

private:
    QHBoxLayout *layout = nullptr;  //横向布局

    QColor bgColor = Qt::lightGray; //背景颜色
    int areaSpacing = 6;        //与area之间的空隙

};

#endif // BUTTONMENU_H
