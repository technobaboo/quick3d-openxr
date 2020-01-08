#ifndef QOPENXRAPPLICATION_H
#define QOPENXRAPPLICATION_H

#include <QObject>
#include <QtQuick3D/private/qquick3dnode_p.h>
#include <QtQuick3D/private/qquick3dsceneenvironment_p.h>
#include <QtQuick3D/private/qquick3dviewport_p.h>

#include "quick3d-openxr_meta.h"

class QQmlEngine;
class QQuickItem;

class QUICK3DOPENXR_EXPORT QOpenXRApplication : public QObject {
    Q_OBJECT
public:
    QOpenXRApplication(QQmlEngine *mainQmlEngine, QQmlComponent *sceneComponent);
    virtual ~QOpenXRApplication();

    Q_INVOKABLE void setEnvironment(QQuick3DSceneEnvironment *environment);
//    void setSceneRoot(QQuick3DObject *root);

protected:
    OpenXR *openxr;
    OpenGL *opengl;
    OpenXRGraphics *graphics;

//    QQmlEngine *mainQmlEngine;
    QObject *sceneObject;
    QQuickItem *rootItem;

    QQuick3DViewport *leftView;
    QQuick3DViewport *rightView;

    QQuick3DNode *sceneRoot;
    QQuick3DSceneEnvironment *environment;
};

#endif // QOPENXRAPPLICATION_H
