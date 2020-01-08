#include <QGuiApplication>
#include <QQmlEngine>
#include <QOpenXRApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QGuiApplication a(argc, argv);

    //Create QML engine
    QQmlEngine *mainQmlEngine = new QQmlEngine();
    QQmlComponent *sceneComponent = new QQmlComponent(mainQmlEngine, QUrl("qrc:/xrgears.qml"), QQmlComponent::PreferSynchronous);
    if(sceneComponent->isError()) {
        qDebug() << "QML errors:" << sceneComponent->errors() << endl;
    }

//    QOpenXRApplication *xrApp = new QOpenXRApplication(mainQmlEngine, sceneComponent);

    //Add QML access to this instance
    qmlRegisterSingletonType<QOpenXRApplication *>("QtQuick3D", 1, 0, "OpenXR", [mainQmlEngine, sceneComponent](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        return new QOpenXRApplication(mainQmlEngine, sceneComponent);
    });

    return a.exec();
}
