#include <QQmlEngine>
#include <QQuickItem>
#include "qopenxrapplication.h"

#include <QDebug>

QOpenXRApplication::QOpenXRApplication(QString qmlPath) : QObject(nullptr) {
    qDebug() << "Creating new OpenXR session" << endl;

    mainQmlEngine = new QQmlEngine();

    //Create QML component
    QQmlComponent *rootComponent = new QQmlComponent(mainQmlEngine, qmlPath, QQmlComponent::PreferSynchronous);

    //Load in the QML and add it to the window
    rootObject = qobject_cast<QQuickItem *>(graphics->qmlComponent->create());
    //    graphics->rootObject = rootObject;
}

QOpenXRApplication::~QOpenXRApplication() {

}
