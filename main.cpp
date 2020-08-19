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
        int res = a.exec();

        QList<QWidget*> widgetList = QApplication::allWidgets();
        for(auto widget : widgetList) {
            if(widget->isTopLevel()) {
                widget->close();
            }
        }

        return res;
    }

    return 0;
}
