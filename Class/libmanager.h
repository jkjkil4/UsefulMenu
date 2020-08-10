#ifndef LIBMANAGER_H
#define LIBMANAGER_H

#include <QWidget>
#include <QLibrary>
#include <QFileInfo>

typedef void(QWidget::*ShowFunc)();

class LibManager
{
public:
    typedef void(*FuncMain)();
    typedef QString(*FuncLibName)();
    typedef QPixmap(*FuncLibPixmap)();
    typedef void(*FuncSetShowFuncPtr)(QWidget*, ShowFunc);

    LibManager(QLibrary* lib) : lib(lib) {
        FuncLibName funcLibName = (FuncLibName)lib->resolve("getLibName");
        if(funcLibName) {
            libName = QString((*funcLibName)());
        } else {
            QString fileName = QFileInfo(lib->fileName()).fileName();
            libName = fileName.left(fileName.lastIndexOf('.'));
        }

        FuncLibPixmap funcLibPixmap = (FuncLibPixmap)lib->resolve("getLibPixmap");
        if(funcLibPixmap) {
            libPixmap = (*funcLibPixmap)();
        }

        funcMain = (FuncMain)lib->resolve("Main");
        setShowFuncPtr = (FuncSetShowFuncPtr)lib->resolve("setShowFuncPtr");

    }

    QLibrary* lib;
    QString libName;
    QPixmap libPixmap;

    FuncMain funcMain;
    void fMain() {
        if(funcMain)
            (*funcMain)();
    }

    FuncSetShowFuncPtr setShowFuncPtr;
    void fSetShowFuncPtr(QWidget* funcWidget, ShowFunc func) {
        if(setShowFuncPtr)
            (setShowFuncPtr)(funcWidget, func);
    }
};

#endif // LIBMANAGER_H
