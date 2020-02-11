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
    Q_PROPERTY(QVector3D gazePosition READ getGazePosition NOTIFY gazePositionChanged)
    Q_PROPERTY(QVector3D gazeDirection READ getGazeDirection NOTIFY gazeDirectionChanged)
public:
    QOpenXRApplication(QObject *parent = nullptr);
    virtual ~QOpenXRApplication();

    void initialize(QQmlEngine *engine, QQmlComponent *component);
    Q_INVOKABLE void setEnvironment(QQuick3DSceneEnvironment *environment);
//    void setSceneRoot(QQuick3DObject *root);

    QVector3D getGazePosition() const;
    QVector3D getGazeDirection() const;

signals:
    void ready();
    void frame();
    void gazePositionChanged();
    void gazeDirectionChanged();

protected slots:
    void renderReady();
    void renderFrame();

protected:
    QObject *sceneObject;
    QQuickItem *rootItem;

    QQmlEngine *mainQmlEngine;
    QQmlComponent *sceneComponent;

    QQuick3DNode *sceneRoot;
    QQuick3DSceneEnvironment *environment;
    OpenXRRenderThread *renderThread;

    QVector3D gazePosition;
    QVector3D gazeDirection;
};

#endif // QOPENXRAPPLICATION_H
