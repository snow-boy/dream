#ifndef LIFE_GLOBAL_H
#define LIFE_GLOBAL_H

#include <qglobal.h>

#if defined(LIFE_LIBRARY)
#  define LIFE_DECL Q_DECL_EXPORT
#else
#  define LIFE_DECL Q_DECL_IMPORT
#endif

#endif // LIFE_GLOBAL_H
