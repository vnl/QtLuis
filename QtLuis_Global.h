#ifndef QTLUIS_GLOBAL_H
#define QTLUIS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTLUIS_LIBRARY)
#  define QTLUISSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTLUISSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTLUIS_GLOBAL_H
