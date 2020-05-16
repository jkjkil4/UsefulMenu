#include "getscreen.h"

GetScreen::GetScreen(QImage *img)
    : img(img)
{
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SubWindow | Qt::FramelessWindowHint);
    //close时销毁
    setAttribute(Qt::WA_DeleteOnClose);

    resize(QApplication::primaryScreen()->size());
    move(0, 0);
}
