#include <QGuiApplication>
#include <QOpenXRApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QGuiApplication a(argc, argv);

    QOpenXRApplication *xrApp = new QOpenXRApplication(QUrl("qrc://xrgears.qml"));

    return a.exec();
}
