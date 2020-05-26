#ifndef PATHBTN_H
#define PATHBTN_H

#include <QAbstractButton>

#include <QFileIconProvider>

#include "Class/global.h"

class PathBtn : public QAbstractButton
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent *) override {}
    void keyReleaseEvent(QKeyEvent *) override {}
    void paintEvent(QPaintEvent *) override;

public:
    explicit PathBtn(QString path, QWidget *parent = nullptr);
    ~PathBtn() override = default;

    bool isMouseAt();

    VARIBLE_FUNC(Path, path, QString)

    //和大小相关的一些东西
    SC int bWidth = 56;
    SC int bHeight = 56;
    SC int borderSize = 2;

    //和颜色相关的一些东西
    SC QRgb colBorder = qRgb(10, 100, 196);

    SC QRgb colNormal = qRgb(100, 100, 100);
    SC QRgb colHolding = qRgb(85, 85, 85);

private:
    QString path;
    QString fileName;
    QPixmap pathIcon;
};

#endif // PATHBTN_H
