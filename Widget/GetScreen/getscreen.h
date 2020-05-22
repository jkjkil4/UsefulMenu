#ifndef GETSCREEN_H
#define GETSCREEN_H

#include <QDialog>
#include <QApplication>
#include <QScreen>

#include <QTimer>

class AreaParent;
class AreaPoint;

class ButtonMenu;

class IconBtn;
class ImgView;

inline QImage getScreenImage() {
    return QApplication::primaryScreen()->grabWindow(0).toImage();
}

class GetScreen : public QDialog
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

private:
    struct Area
    {
        int x1 = 0, y1 = 0;
        int x2 = 0, y2 = 0;
    }area;

    QCursor alignMap[3][3]{
        {Qt::SizeFDiagCursor, Qt::SizeVerCursor, Qt::SizeBDiagCursor},
        {Qt::SizeHorCursor,   Qt::SizeAllCursor, Qt::SizeHorCursor},
        {Qt::SizeBDiagCursor, Qt::SizeVerCursor, Qt::SizeFDiagCursor}
    };

public:
    explicit GetScreen(QImage *img);
    ~GetScreen() override;

    void addBtn(ButtonMenu *menu, IconBtn *btn);

    void setControlerVisible(bool on);

   QCursor getCursorType(int flags);

   QString getSaveFileName();
   QString getMS();

public slots:
    void onAreaChanged();
    void onChangeAreaTimeout();
    void onAreaChangeDone();

    void onBtnSavePressed();
    void onBtnSaveAsPressed();
    void onBtnCancelPressed();
    void onBtnAcceptPressed();

private:
    QImage *img = nullptr;

    //区域的控制控件
    QVector<AreaParent*> areaWidgets;
    QVector<AreaPoint*> areaPoints;
    //区域是否被改变
    bool isAreaChanged = false;

    //大图显示
    ImgView *imgView = nullptr;

    //按钮菜单
    IconBtn *btnSave = nullptr;
    ButtonMenu *btnMenu = nullptr;

    QTimer *changeArea = new QTimer(this);

    QRect cutRect;

    bool isFirstMove = true;

};

#endif // GETSCREEN_H
