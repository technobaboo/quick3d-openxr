# Qt Quick 3D OpenXR Module
![XRGears demo](https://github.com/technobaboo/quick3d-openxr/blob/master/examples/quick3d-openxr/xrgears/doc/screenshot.png?raw=true)

This is a module, made using Qt 5.14.0, that speeds up the creation of OpenXR applications for Qt Quick 3D.

##Installation
1. Install Monado (https://gitlab.freedesktop.org/monado/monado) and ensure xrgears runs
2. Install Qt 5.14.1 base, QML, Quick and Quick 3D via package manager, Qt's website (https://www.qt.io/download), or compile it yourself (https://github.com/qt)
3. Build Quick3D-OpenXR using the provided scripts (make sure qmake is in your PATH):
```
$ mkdir build && cd build
$ sh ../scripts/build.sh ..
```

## Basic Usage Guide
Quick3D-OpenXR does most of the work connecting to OpenXR and setting up Qt Quick 3D. But there are still a few steps you need to do:

In `int main` in main.cpp:
1. Create a `QGuiApplication`
2. Create a `QOpenXRApplication`
3. Register any QML types you need to
4. Create a `QQmlEngine`
5. Create a `QQmlComponent` loading the QML for the main scene synchronously
6. Initialize the `QOpenXRApplication`

Example main.cpp:
```cpp
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

    xrApp->initialize(mainQmlEngine, sceneComponent);

    return a.exec();
}
```
