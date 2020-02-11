#include <QQmlEngine>
#include <QQmlError>
#include <QQuickItem>
#include "qopenxrapplication.h"

#include <QtQuick3D/private/qquick3dfrustumcamera_p.h>

#include <QDebug>

QOpenXRApplication::QOpenXRApplication(QObject *parent) : QObject(parent) {
    sceneRoot = new QQuick3DNode();
}

QOpenXRApplication::~QOpenXRApplication() {

}

void QOpenXRApplication::initialize(QQmlEngine *engine, QQmlComponent *component) {
    qDebug() << "Creating new OpenXR session" << endl;

    mainQmlEngine = engine;
    sceneComponent = component;

    if(sceneComponent->isError()) {
        qDebug() << "QML errors:" << sceneComponent->errors() << endl;
    }

    renderThread = new OpenXRRenderThread(sceneRoot, mainQmlEngine);
    connect(renderThread, &OpenXRRenderThread::renderReady, this, &QOpenXRApplication::renderReady, Qt::QueuedConnection);
    connect(renderThread, &OpenXRRenderThread::renderFrame, this, &QOpenXRApplication::renderFrame, Qt::QueuedConnection);
    sceneRoot->moveToThread(renderThread);
    renderThread->start(QThread::TimeCriticalPriority);
}

void QOpenXRApplication::setEnvironment(QQuick3DSceneEnvironment *environment) {
    qDebug() << "Set Environment Map" << endl;
    renderThread->leftView ->setEnvironment(environment);
    renderThread->rightView->setEnvironment(environment);
    this->environment = environment;
}

void QOpenXRApplication::renderReady() {
    //Create QML component for the scene and instantiate an instance
    sceneObject = sceneComponent->create();
    QQuick3DObject *scene3DObject = qobject_cast<QQuick3DObject *>(sceneObject);
    scene3DObject->setParentItem(sceneRoot);
    scene3DObject->setParent(sceneRoot);

    emit ready();
}

void QOpenXRApplication::renderFrame() {
    gazePosition = (renderThread->leftCamera->scenePosition() + renderThread->rightCamera->scenePosition())/2;
    gazeDirection = (renderThread->leftCamera->forward() + renderThread->rightCamera->forward())/2;

    emit gazePositionChanged();
    emit gazeDirectionChanged();
    emit frame();
}

QVector3D QOpenXRApplication::getGazeDirection() const
{
    return gazeDirection;
}

QVector3D QOpenXRApplication::getGazePosition() const
{
    return gazePosition;
}

//void QOpenXRApplication::setSceneRoot(QQuick3DObject root) {
//    sceneRoot = root;
//    root.setParentItem()
//}
