#ifndef OBJECT_ACCESSOR_GLOBAL_H
#define OBJECT_ACCESSOR_GLOBAL_H

#ifdef __OS_XUN__
#   define DECL_EXPORT __attribute__((visibility("default")))
#   define DECL_IMPORT
#else
#   define DECL_EXPORT __declspec(dllexport)
#   define DECL_IMPORT __declspec(dllimport)
#endif

#if defined(USE_OBJECT_ACCESSOR_STATIC)
#define S2_DECL
#else

#if defined(OBJECT_ACCESSOR_LIBRARY)
#  define OBJECT_ACCESSOR_DECL DECL_EXPORT
#else
#  define OBJECT_ACCESSOR_DECL DECL_IMPORT
#endif

#endif


#endif // OBJECT_ACCESSOR_GLOBAL_H
