#include "mainwidget.h"

#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSharedMemory sharedMem;
    sharedMem.setKey(QString("UsefulMenu_SharedMem"));
    if(sharedMem.attach()){
        QMessageBox::information(nullptr, "提示", "程序正在运行");
        return 0;
    }

    if(sharedMem.create(1)) {
        MainWidget w;
        return a.exec();
    }

    return 0;
}
