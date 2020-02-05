#ifndef QOPENXRAPPLICATION_H
#define QOPENXRAPPLICATION_H

#include <QObject>
#include <QtQuick3D/private/qquick3dnode_p.h>
#include <QtQuick3D/private/qquick3dsceneenvironment_p.h>
#include <QtQuick3D/private/qquick3dviewport_p.h>

#include "openxrrenderthread.h"

class QQmlEngine;
class QQuickItem;

class QUICK3DOPENXR_EXPORT QOpenXRApplication : public QObject {
    Q_OBJECT
public:
    QOpenXRApplication(QObject *parent = nullptr);
    virtual ~QOpenXRApplication();

    void initialize(QQmlEngine *engine, QQmlComponent *component);
    Q_INVOKABLE void setEnvironment(QQuick3DSceneEnvironment *environment);
//    void setSceneRoot(QQuick3DObject *root);

signals:
    void ready();

protected slots:
    void renderReady();

protected:
    QObject *sceneObject;
    QQuickItem *rootItem;

    QQmlEngine *mainQmlEngine;
    QQmlComponent *sceneComponent;

    QQuick3DNode *sceneRoot;
    QQuick3DSceneEnvironment *environment;
    OpenXRRenderThread *renderThread;
};

#endif // QOPENXRAPPLICATION_H
