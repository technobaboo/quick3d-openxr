#include <QQmlEngine>
#include <QQuickItem>
#include "qopenxrapplication.h"

#include <QtQuick3D/private/qquick3dfrustumcamera_p.h>
#include <QtQuick3D/private/qquick3dviewport_p.h>

#include <QDebug>

QOpenXRApplication::QOpenXRApplication(QString qmlPath) : QObject(nullptr) {
    qDebug() << "Creating new OpenXR session" << endl;

    //Create QML engine
    mainQmlEngine = new QQmlEngine();

    //Create QML component for the scene and instantiate an instance
    QQmlComponent *sceneComponent = new QQmlComponent(mainQmlEngine, qmlPath, QQmlComponent::PreferSynchronous);
    sceneObject = sceneComponent->create();
    QQuick3DObject *scene3DObject = qobject_cast<QQuick3DObject *>(sceneObject);

    //Create all OpenXR object classes
    opengl = new OpenGL();
    openxr = new OpenXR();
    graphics = new OpenXRGraphics();

    //Link everything together
    opengl->openxr = openxr;
    openxr->opengl = opengl;
    opengl->graphics = graphics;
    graphics->openxr = openxr;
    graphics->qmlEngine = mainQmlEngine;

    //Set up the window
    graphics->preInitialize();
    QQuick3DViewport *leftView  = new QQuick3DViewport(graphics->window->contentItem());
    QQuick3DViewport *rightView = new QQuick3DViewport(graphics->window->contentItem());

    //Align and size the viewports
    leftView ->setSize(graphics->leftViewSize );
    rightView->setSize(graphics->rightViewSize);
    rightView->setPosition(QPoint(graphics->leftViewSize.width(), 0));

    //Set the rendering modes for the viewports
    leftView ->setRenderMode(QQuick3DViewport::RenderMode::Inline);
    rightView->setRenderMode(QQuick3DViewport::RenderMode::Inline);

    //Create the base node for the entire QtQuick3D scenegraph and add the QML component contents in
    sceneRoot = new QQuick3DNode();
    sceneRoot->setParent(graphics->window->contentItem());
    if(scene3DObject != nullptr)
        scene3DObject->setParentItem(sceneRoot);

    //Add in the cameras for the scenegraph
    QQuick3DFrustumCamera *leftCamera  = new QQuick3DFrustumCamera();
    QQuick3DFrustumCamera *rightCamera = new QQuick3DFrustumCamera();

    leftCamera ->setParentItem(sceneRoot);
    rightCamera->setParentItem(sceneRoot);

    //Link the viewports to the cameras and scenes
    leftView ->setCamera(leftCamera );
    rightView->setCamera(rightCamera);

    leftView ->setImportScene(sceneRoot);
    rightView->setImportScene(sceneRoot);

    //Link the cameras to the graphics
    graphics->cameras = {leftCamera, rightCamera};

    //Add QML access to this instance
//    qmlRegisterSingletonType<QOpenXRApplication *>("QtQuick3D", 1, 0, "OpenXR", [this](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
//        Q_UNUSED(engine)
//        Q_UNUSED(scriptEngine)

//        return this;
//    });

    openxr->initialize();
    graphics->initialize();
}

QOpenXRApplication::~QOpenXRApplication() {

}
