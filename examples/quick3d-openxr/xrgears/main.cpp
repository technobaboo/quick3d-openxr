#include <QCoreApplication>
#include <QOpenXRApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QOpenXRApplication *xrApp = new QOpenXRApplication("qrc:/xrgears.qml");

    return a.exec();
}
