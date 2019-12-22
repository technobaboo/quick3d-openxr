#include "quick3d-openxr_meta.h"

#include <QCoreApplication>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <QtPlatformHeaders/QGLXNativeContext>
#include <string.h>
#include <QDebug>

OpenGL::OpenGL(QObject *parent) : QObject(parent) {
    int fbOptions[11] = {GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_ALPHA_SIZE, 8, None};
    memcpy(&framebufferOptions, &fbOptions, sizeof (fbOptions));
}
void OpenGL::initialize() {
    //Temporarily make the context current
    graphics->glContext->doneCurrent();
    graphics->glContext->makeCurrent(graphics->surface);


    //Get X display
    display = XOpenDisplay(nullptr);

    QVariant nativeGLHandle = graphics->glContext->nativeHandle();

    if (strcmp(nativeGLHandle.typeName(), "QGLXNativeContext") == 0) {
      QGLXNativeContext nativeContext = qvariant_cast<QGLXNativeContext>(nativeGLHandle);
      //display = nativeContext.display();
      context = nativeContext.context();
      drawable = 0x1;
    }

    int nelements = 0;
    framebufferConfig = glXChooseFBConfig(display, 0, framebufferOptions, &nelements);

    //Enable same-thread context checking
    QCoreApplication::setAttribute(Qt::AA_DontCheckOpenGLContextThreadAffinity, false);

    qDebug() << "OpenGL initialized" << endl;
}

