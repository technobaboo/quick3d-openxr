#ifndef STARDUSTOPENXRGRAPHICS_H
#define STARDUSTOPENXRGRAPHICS_H

#include <QObject>
#include <QSize>
#include <QRect>

#include "openxr_meta.h"
#include <QtQuick3D/private/qquick3dfrustumcamera_p.h>

class OpenXR;
class OpenXRFrame;

class QSurfaceFormat;
class QOpenGLContext;
class QOpenGLFramebufferObject;

class QQuickWindow;
class QQuickItem;
class QQuickRenderControl;
class QQmlComponent;
class QQmlEngine;
class QOffscreenSurface;

class OpenXRGraphics : public QObject {
    Q_OBJECT
public:
    explicit OpenXRGraphics(QObject *parent = nullptr);
    ~OpenXRGraphics();

    OpenXR *openxr = nullptr;
    void setupQtRendering();
    void getViewSizes();
    void initialize();

    uint displayFPS = 0;

    XrViewConfigurationProperties viewProperties{XR_TYPE_VIEW_CONFIGURATION_PROPERTIES};
    XrViewConfigurationView eyeData[2];

    XrSwapchainCreateInfo swapInfo = {
        XR_TYPE_SWAPCHAIN_CREATE_INFO,                                                      //XrStructureType           type;
        nullptr,                                                                            //const void*               next;
        0,                                                                                  //XrSwapchainCreateFlags    createFlags;
        XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT | XR_SWAPCHAIN_USAGE_TRANSFER_DST_BIT,      //XrSwapchainUsageFlags     usageFlags;
        GL_RGBA8,                                                                           //int64_t                   format;
        1,                                                                                  //uint32_t                  sampleCount;
        1,                                                                                  //uint32_t                  width;
        1,                                                                                  //uint32_t                  height;
        1,                                                                                  //uint32_t                  faceCount;
        1,                                                                                  //uint32_t                  arraySize;
        1                                                                                   //uint32_t                  mipCount;
    };
    XrSwapchain swapchains[2];

    uint32_t swapchainImageCount = 0;
    XrSwapchainImageOpenGLKHR swapchainImageTemplate = {
        XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR,
        nullptr,
        0
    };
    std::vector<XrSwapchainImageOpenGLKHR> swapchainImages[2];
    uint32_t swapchainImageIndices[2];

    XrReferenceSpaceCreateInfo refSpaceInfo = {
        XR_TYPE_REFERENCE_SPACE_CREATE_INFO,
        nullptr,
        XR_REFERENCE_SPACE_TYPE_STAGE,
        XrPosef {
            XrQuaternionf {0.0f,0.0f,1.0f,0.0f},
            XrVector3f {0.0f,0.0f,0.0f}
        }
    };
    XrSpace refSpace = XR_NULL_HANDLE;

    XrViewLocateInfo viewLocateInfo = {
        XR_TYPE_VIEW_LOCATE_INFO,
        nullptr
    };
    XrViewState viewState = {
        XR_TYPE_VIEW_STATE,
        nullptr
    };

    QRect eyeRects[2];

    XrCompositionLayerProjectionView stardustLayerViews[2] = {
        XrCompositionLayerProjectionView {
            XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW,
            nullptr
        },
        XrCompositionLayerProjectionView {
            XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW,
            nullptr
        }
    };

    QThread *frameThread = nullptr;
    OpenXRFrame *frame = nullptr;

    std::vector<XrView> views;

    std::vector<QQuick3DFrustumCamera *> cameras;

    QSize leftViewSize;
    QSize rightViewSize;

    QSize totalSize;

    QSurfaceFormat *glFormat;
    QOpenGLContext *glContext;
    QOffscreenSurface *surface;
    QQuickWindow *window;
    QQuickRenderControl *quickRenderer;
    QOpenGLFramebufferObject *glFBO;

    QQmlEngine *qmlEngine;
    QQmlComponent *qmlComponent;

    std::vector<GLuint>openglImages[2];

    XrFrameWaitInfo frameWaitInfo{XR_TYPE_FRAME_WAIT_INFO};
    XrFrameState frameState{XR_TYPE_FRAME_STATE};

signals:
    void startFrameLoop();
};


#endif // STARDUSTOPENXRGRAPHICS_H
