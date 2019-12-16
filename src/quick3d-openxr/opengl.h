#ifndef STARDUSTOPENGL_H
#define STARDUSTOPENGL_H

#include <QQuickWindow>

#include "openxr_meta.h"

class OpenXR;
class OpenXRGraphics;

class OpenGL : public QObject
{
    Q_OBJECT
public:
    explicit OpenGL(QObject *parent = nullptr);

    Q_INVOKABLE void initialize();

    Display *display;

    GLXContext context;
    GLXDrawable drawable;
    GLXFBConfig *framebufferConfig;

    int framebufferOptions[11];

    OpenXR *openxr;
    OpenXRGraphics *graphics;
};


#endif // STARDUSTOPENGL_H
