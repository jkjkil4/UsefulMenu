#ifndef LIBMANAGER_H
#define LIBMANAGER_H

#include <QWidget>
#include <QLibrary>
#include <QFileInfo>
#include <QMenu>

typedef void(QWidget::*ShowFunc)();

class LibManager
{
public:
    typedef QString(*FuncLibName)();
    typedef QPixmap(*FuncLibPixmap)();

    typedef void(*FuncMain)(QWidget*);
    typedef void(*FuncSetShowFuncPtr)(QWidget*, ShowFunc);

    typedef void(*FuncAppendAction)(QMenu*);
    typedef void(*FuncCheckAction)(QAction*);

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
        appendAction = (FuncAppendAction)lib->resolve("appendAction");
        checkAction = (FuncCheckAction)lib->resolve("checkAction");
    }

    QLibrary* lib;
    QString libName;
    QPixmap libPixmap;

    void fMain(QWidget* widget) {
        if(funcMain)
            (*funcMain)(widget);
    }
    void fSetShowFuncPtr(QWidget* funcWidget, ShowFunc func) {
        if(setShowFuncPtr)
            (*setShowFuncPtr)(funcWidget, func);
    }
    void fAppendAction(QMenu *menu) {
        if(appendAction)
            (*appendAction)(menu);
    }
    void fCheckAction(QAction *resAction) {
        if(checkAction)
            (*checkAction)(resAction);
    }


private:
    FuncMain funcMain;
    FuncSetShowFuncPtr setShowFuncPtr;
    FuncAppendAction appendAction;
    FuncCheckAction checkAction;
};

#endif // LIBMANAGER_H
