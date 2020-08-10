#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include "screenshot_global.h"

#include "header.h"

#include <QDialog>
#include <QMessageBox>

#include <QApplication>
#include <QScreen>
#include <QSettings>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include <QClipboard>
#include <QKeyEvent>
#include <QPainter>

extern "C" {
    SCREENSHOTSHARED_EXPORT QString getLibName();
    SCREENSHOTSHARED_EXPORT QPixmap getLibPixmap();

    SCREENSHOTSHARED_EXPORT void Main();
}

class AreaParent;
class AreaPoint;

class ButtonMenu;

class IconBtn;
class ImgView;

class Screenshot : public QDialog
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

private:
    struct Area
    {
        int x1 = 0, y1 = 0;
        int x2 = 0, y2 = 0;
        QRect rect() {
            return QRect(QPoint(qMin(x1, x2), qMin(y1, y2)), QPoint(qMax(x1, x2), qMax(y1, y2)));
        }
        void reset() {
            x1 = 0;
            x2 = 0;
            y1 = 0;
            y2 = 0;
        }
    }area;

    Qt::CursorShape alignMap[3][3]{
        {Qt::SizeFDiagCursor, Qt::SizeVerCursor, Qt::SizeBDiagCursor},
        {Qt::SizeHorCursor,   Qt::SizeAllCursor, Qt::SizeHorCursor},
        {Qt::SizeBDiagCursor, Qt::SizeVerCursor, Qt::SizeFDiagCursor}
    };

public:
    explicit Screenshot(QImage& img);
    ~Screenshot() override;

    void addBtn(ButtonMenu *menu, IconBtn *btn);

    void setControlerVisible(bool on);

    QCursor getCursorType(int flags);

    static QString getSaveFileName();
    static QString getMS();
    static void saveImage(const QImage& img, const QRect& rect, const QString& path, QWidget* boxParent = nullptr);

public slots:
    void onAreaChanged();
    void onChangeAreaTimeout();
    void onAreaChangeDone();

    void onBtnSavePressed();
    void onBtnSaveAsPressed();
    void onBtnCancelPressed();
    void onBtnAcceptPressed();

private:
    QImage& img;

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

#endif // SCREENSHOT_H
