#include "openxrrenderthread.h"

OpenXRRenderThread::OpenXRRenderThread(QQuick3DNode *sceneRoot, QQmlEngine *engine) : QThread(sceneRoot) {
    mainQmlEngine = engine;
    this->sceneRoot = sceneRoot;
}

void OpenXRRenderThread::run() {

    //Create all OpenXR object classes
    opengl = new OpenGL();
    openxr = new OpenXR();
    graphics = new OpenXRGraphics();
    frame = new OpenXRFrame();

    //Link everything together
    opengl->openxr = openxr;
    openxr->opengl = opengl;
    opengl->graphics = graphics;
    graphics->openxr = openxr;
    graphics->qmlEngine = mainQmlEngine;
    frame->graphics = graphics;

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

    graphics->initialize();

    sceneRoot->moveToThread(QCoreApplication::instance()->thread());
    emit renderReady();
    frame->initialize();
}
