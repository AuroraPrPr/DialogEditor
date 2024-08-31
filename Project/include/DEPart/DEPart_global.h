#ifndef DEPART_GLOBAL_H
#define DEPART_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEPART_LIBRARY)
#  define DEPART_EXPORT Q_DECL_EXPORT
#else
#  define DEPART_EXPORT Q_DECL_IMPORT
#endif

#endif // DEPART_GLOBAL_H
