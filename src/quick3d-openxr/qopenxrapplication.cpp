#include <QQmlEngine>
#include <QQmlError>
#include <QQuickItem>
#include "qopenxrapplication.h"

#include <QtQuick3D/private/qquick3dfrustumcamera_p.h>

#include <QDebug>

QOpenXRApplication::QOpenXRApplication(QQmlEngine *mainQmlEngine, QQmlComponent *sceneComponent) : QObject(nullptr) {
    qDebug() << "Creating new OpenXR session" << endl;

    //Add QML access to this instance
    qmlRegisterSingletonInstance<QOpenXRApplication>("QtQuick3D", 1, 0, "OpenXR", this);

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

    //Set up OpenXR
    openxr->setupInfo();
    openxr->loadExtensions();
    openxr->createInstance();
    openxr->loadSystem();
    graphics->setupQtRendering();
    opengl->initialize();
    openxr->setupGraphics();
    openxr->createSession();
    openxr->startSession();
    graphics->getViewSizes();

    //Set up the window
    leftView  = new QQuick3DViewport(graphics->window->contentItem());
    rightView = new QQuick3DViewport(graphics->window->contentItem());

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

    //Create QML component for the scene and instantiate an instance
    sceneObject = sceneComponent->create();
    QQuick3DObject *scene3DObject = qobject_cast<QQuick3DObject *>(sceneObject);
    if(scene3DObject != nullptr)
        scene3DObject->setParentItem(sceneRoot);

    graphics->initialize();
}

QOpenXRApplication::~QOpenXRApplication() {

}

void QOpenXRApplication::setEnvironment(QQuick3DSceneEnvironment *environment) {
    leftView ->setEnvironment(environment);
    rightView->setEnvironment(environment);
    this->environment = environment;
}

//void QOpenXRApplication::setSceneRoot(QQuick3DObject root) {
//    sceneRoot = root;
//    root.setParentItem()
//}
