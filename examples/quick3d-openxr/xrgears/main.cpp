#include <QGuiApplication>
#include <QQmlEngine>
#include <QOpenXRApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QGuiApplication a(argc, argv);

    QOpenXRApplication *xrApp = new QOpenXRApplication(nullptr);
    qmlRegisterSingletonInstance<QOpenXRApplication>("QtQuick3D.OpenXR", 1, 0, "OpenXR", xrApp);

    QQmlEngine *mainQmlEngine = new QQmlEngine();
    QQmlComponent *sceneComponent = new QQmlComponent(mainQmlEngine, QUrl("qrc:/xrgears.qml"), QQmlComponent::PreferSynchronous);

    if(sceneComponent->isError()) {
        qDebug() << "QML errors:" << sceneComponent->errors() << endl;
    }

    xrApp->initialize(mainQmlEngine, sceneComponent);

    return a.exec();
}
