#ifndef OPENXRRENDERTHREAD_H
#define OPENXRRENDERTHREAD_H

#include <QObject>
#include <QThread>
#include <QElapsedTimer>

#include <QtQuick3D/private/qquick3dnode_p.h>
#include <QtQuick3D/private/qquick3dsceneenvironment_p.h>
#include <QtQuick3D/private/qquick3dviewport_p.h>

#include "quick3d-openxr_meta.h"

class OpenXRRenderThread : public QThread
{
    Q_OBJECT
    void run();
public:
    explicit OpenXRRenderThread(QQuick3DNode *sceneRoot, QQmlEngine *engine);

    OpenXR *openxr;
    OpenGL *opengl;
    OpenXRGraphics *graphics;
    OpenXRFrame *frame;

    QQmlEngine *mainQmlEngine;

    QQuick3DNode *sceneRoot;

    QQuick3DViewport *leftView;
    QQuick3DViewport *rightView;

signals:
    void renderReady();
    void renderFrame();

private:
    //FPS Timing
    QElapsedTimer *frameTimer;
    float fps = 0;
};

#endif // OPENXRRENDERTHREAD_H
