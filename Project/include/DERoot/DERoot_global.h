#ifndef DEROOT_GLOBAL_H
#define DEROOT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEROOT_LIBRARY)
#  define DEROOT_EXPORT Q_DECL_EXPORT
#else
#  define DEROOT_EXPORT Q_DECL_IMPORT
#endif

#endif // DEROOT_GLOBAL_H
