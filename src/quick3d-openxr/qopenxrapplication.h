#ifndef QOPENXRAPPLICATION_H
#define QOPENXRAPPLICATION_H

#include "quick3d-openxr_meta.h"

class OpenGL;
class OpenXR;
class OpenXRGraphics;
class OpenXRFrame;
class QQmlEngine;
class QQuickItem;

class QUICK3DOPENXR_EXPORT QOpenXRApplication : public QObject {
    Q_OBJECT
public:
    QOpenXRApplication(QString qmlPath);
    virtual ~QOpenXRApplication();


    OpenXR *openxr;
    OpenGL *opengl;
    OpenXRGraphics *graphics;

    QQmlEngine *mainQmlEngine;
    QQuickItem *rootObject;
};

#endif // QOPENXRAPPLICATION_H
