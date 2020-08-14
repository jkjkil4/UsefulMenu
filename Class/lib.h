#ifndef LIB_H
#define LIB_H

#include <QLibrary>

struct Lib {
    QLibrary* lib;
    bool isEnabled;
};

#endif // LIB_H
