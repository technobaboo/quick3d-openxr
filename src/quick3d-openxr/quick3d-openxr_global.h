#include <QtCore/QtGlobal>

#if defined(QUICK3DOPENXR_MODULE)
    #define QUICK3DOPENXR_EXPORT Q_DECL_EXPORT
#else
    #define QUICK3DOPENXR_EXPORT Q_DECL_IMPORT
#endif
