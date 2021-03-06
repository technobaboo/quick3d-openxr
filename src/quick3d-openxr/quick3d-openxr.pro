TARGET = Quick3DOpenXR
MODULE = quick3d-openxr

QT += qml quick quick3d-private openglextensions
CONFIG += c++11

LIBS += -lopenxr_loader \
        -lGLEW \
        -lglfw \
        -lX11

DEFINES += QUICK3DOPENXR_MODULE

SOURCES += \
    openxrrenderthread.cpp \
    qopenxrapplication.cpp \
    opengl.cpp \
    openxr.cpp \
    openxrgraphics.cpp \
    openxrframe.cpp

HEADERS += \
    opengl_meta.h \
    openxr_meta.h \
    opengl.h \
    openxr.h \
    openxrgraphics.h \
    openxrframe.h \
    openxrrenderthread.h \
    qopenxrapplication.h \
    quick3d-openxr_global.h \
    quick3d-openxr_meta.h

load(qt_module)
