#ifndef GETSCREEN_H
#define GETSCREEN_H

#include <QDialog>
#include <QApplication>
#include <QScreen>

inline QImage getScreenImage() {
    return QApplication::primaryScreen()->grabWindow(0).toImage();
}

class GetScreen : public QDialog
{
    Q_OBJECT
public:
    explicit GetScreen(QImage *img);
    ~GetScreen() = default;

    QImage *img = nullptr;
};

#endif // GETSCREEN_H
