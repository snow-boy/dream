#pragma once

#include <qglobal.h>

#if defined(CRADLE_LIBRARY)
#  define CRADLE_DECL Q_DECL_EXPORT
#else
#  define CRADLE_DECL Q_DECL_IMPORT
#endif
