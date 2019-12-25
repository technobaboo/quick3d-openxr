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

    nativeGLHandle = graphics->glContext->nativeHandle();
}

Display *OpenGL::display() {
    return XOpenDisplay(nullptr);
}

GLXContext OpenGL::context() {
    if (strcmp(nativeGLHandle.typeName(), "QGLXNativeContext") == 0) {
        QGLXNativeContext nativeContext = qvariant_cast<QGLXNativeContext>(nativeGLHandle);
        return nativeContext.context();
    }
}

GLXDrawable OpenGL::drawable() {
    return 0x1;
}

GLXFBConfig *OpenGL::framebufferConfig() {
    int nelements = 0;
    return glXChooseFBConfig(display(), 0, framebufferOptions, &nelements);
}
