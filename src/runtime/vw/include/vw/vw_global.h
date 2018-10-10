#ifndef VW_GLOBAL_H
#define VW_GLOBAL_H

#include <qglobal.h>

#if defined(VW_LIBRARY)
#  define VW_DECL Q_DECL_EXPORT
#else
#  define VW_DECL Q_DECL_IMPORT
#endif

#endif // VW_GLOBAL_H
