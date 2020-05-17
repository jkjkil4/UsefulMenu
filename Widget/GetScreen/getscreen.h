#ifndef GETSCREEN_H
#define GETSCREEN_H

#include <QDialog>
#include <QApplication>
#include <QScreen>

#include <QTimer>

class AreaPoint;

inline QImage getScreenImage() {
    return QApplication::primaryScreen()->grabWindow(0).toImage();
}

class GetScreen : public QDialog
{
    Q_OBJECT
protected:
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

    void setControlerVisible(bool on);

   QCursor getCursorType(int flags);

public slots:
    void onAreaChanged();
    void onChangeAreaTimeout();
    void onAreaChangeDone();

private:
    QImage *img = nullptr;

    QVector<AreaPoint*> areaPoints;
    //QVector<Area>

    QTimer *changeArea = new QTimer(this);
};

#endif // GETSCREEN_H