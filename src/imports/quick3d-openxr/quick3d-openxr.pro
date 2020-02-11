CXX_MODULE = qml
TARGET = qquick3dplugin
TARGETPATH = QtQuick3D
IMPORT_VERSION = 1.$$QT_MINOR_VERSION

QT += qml-private quick3d-private quick3d-openxr

OTHER_FILES += \
    qmldir

load(qml_plugin)

SOURCES += \
    plugin.cpp
