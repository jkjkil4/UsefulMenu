#ifndef LIBMANAGER_H
#define LIBMANAGER_H

#include <QWidget>
#include <QLibrary>

class LibManager
{
public:
    typedef QWidget*(*FuncNewHandle)();

    LibManager(QLibrary* lib) : lib(lib) {
        newHandle = (FuncNewHandle)lib->resolve("newHandle");
    }

    QLibrary* lib;

    FuncNewHandle newHandle;
    void fNewHandle() {
        if(newHandle) {
            QWidget* widget = (*newHandle)();
            widget->setAttribute(Qt::WA_DeleteOnClose, true);
        }
    }
};

#endif // LIBMANAGER_H
