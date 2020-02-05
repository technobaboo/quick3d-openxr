#ifndef STARDUSTOPENXRFRAME_H
#define STARDUSTOPENXRFRAME_H

#include <QObject>

//#include <GL/glew.h>
//#include <GL/gl.h>

#include "openxr_meta.h"

#include <QElapsedTimer>

class OpenXRGraphics;

class OpenXRFrame : public QObject {
    Q_OBJECT
    Q_PROPERTY(OpenXRGraphics *graphics MEMBER graphics)
public:
    explicit OpenXRFrame(QObject *parent = nullptr);

    OpenXRGraphics *graphics = nullptr;
    void initialize();

    void startFrame();
    void renderFrame();
    void endFrame();

private:

    void copyFrame(uint i);
    void initRenderControl();

    //OpenGL helper functions
    void createTextureFromFD(int d);

    //OpenGL variables
    GLuint renderbuffer;
    GLuint colorTex;

    //OpenXR declarations
    XrSwapchainImageAcquireInfo acquireInfo{XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO, nullptr};
    XrSwapchainImageWaitInfo waitInfo{XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO, nullptr};
};


#endif // STARDUSTOPENXRFRAME_H
