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

    void initialize();
    Display *display();
    GLXContext context();
    GLXDrawable drawable();
    GLXFBConfig *framebufferConfig();

    OpenXR *openxr;
    OpenXRGraphics *graphics;

protected:
    QVariant nativeGLHandle;
    int framebufferOptions[11];
};


#endif // STARDUSTOPENGL_H
