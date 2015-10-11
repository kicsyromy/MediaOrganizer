#ifndef MEDIAORGANIZER_GLOBAL_H
#define MEDIAORGANIZER_GLOBAL_H

#ifdef __cplusplus
extern "C"
{
#endif

#define UNUSED(var) (void)var;

#if defined(_MSC_VER)
    //  Microsoft
    #define EXPORT_SYMBOL __declspec(dllexport)
    #define IMPORT_SYMBOL __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define EXPORT_SYMBOL __attribute__((visibility("default")))
    #define IMPORT_SYMBOL
#else
    #define EXPORT_SYMBOL
    #define IMPORT_SYMBOL
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#if defined(MO_LIB)
#  define MO_API    IMPORT_SYMBOL
#else
#  define MO_API    EXPORT_SYMBOL
#endif

#ifdef __cplusplus
    #define C_STYLE_BEGIN extern "C" {
    #define C_STYLE_END  }
#else
    #define C_STYLE_BEGIN
    #define C_STYLE_END
#endif

#ifdef __cplusplus
}
#endif

#endif // MEDIAORGANIZER_GLOBAL_H
