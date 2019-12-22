#include <QGuiApplication>
#include <QOpenXRApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QGuiApplication a(argc, argv);

    QOpenXRApplication *xrApp = new QOpenXRApplication("qrc:/xrgears.qml");

    return a.exec();
}
