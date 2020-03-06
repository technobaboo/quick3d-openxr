#include "quick3d-openxr_meta.h"

#include <QThread>
#include <QQuickItem>
#include <QQuickRenderControl>
#include <QOpenGLContext>
#include <QSurfaceFormat>
#include <QOpenGLFramebufferObject>

OpenXRGraphics::OpenXRGraphics(QObject *parent) : QObject(parent) {
}

OpenXRGraphics::~OpenXRGraphics() {
    xrDestroySwapchain(swapchains[0]);
    xrDestroySwapchain(swapchains[1]);
}

void OpenXRGraphics::setupQtRendering() {
    //Set the OpenGL version
    glFormat = new QSurfaceFormat;
    glFormat->setProfile(QSurfaceFormat::CoreProfile);
    glFormat->setRenderableType(QSurfaceFormat::OpenGL);
    glFormat->setMajorVersion(4);
    glFormat->setMinorVersion(3);

    //Create the OpenGL view rendering
    glContext = new QOpenGLContext(this);
    bool contextCreated = glContext->create();

    //Create the offscreen surface
    surface = new QOffscreenSurface;
    surface->setFormat(*glFormat);
    surface->create();

    //Create QQuickRenderControl for both eyes
    quickRenderer = new QQuickRenderControl(this);
    window = new QQuickWindow(quickRenderer);
    window->setColor(Qt::transparent);
}

void OpenXRGraphics::getViewSizes() {
    //Get the stereo views' configuration properties
    xrGetViewConfigurationProperties(*openxr->xrInstance, *openxr->hmdID, openxr->viewConfig, &viewProperties);

    //Get the stereo views' configurations
    uint32_t viewCount = 2;
    xrEnumerateViewConfigurationViews(*openxr->xrInstance, *openxr->hmdID, openxr->viewConfig, viewCount, &viewCount, eyeData);

    //Do all this for both eyes
    for(int i=0; i<2; i++) {
        //Create the eyeRects
        eyeRects[i] = QRect();
        eyeRects[1].setX(eyeData[0].recommendedImageRectHeight + (eyeData[0].recommendedImageRectHeight % 2));

        //Update the eyeRects' extents
        eyeRects[i].setHeight(eyeData[i].recommendedImageRectHeight + (eyeData[i].recommendedImageRectHeight % 2));
        eyeRects[i].setWidth(eyeData[i].recommendedImageRectWidth + (eyeData[i].recommendedImageRectHeight % 2));
    }

    leftViewSize = eyeRects[0].size();
    rightViewSize = eyeRects[1].size();

    totalSize = QSize(
                eyeRects[0].width()+eyeRects[1].width(),
                std::max(eyeRects[0].height(), eyeRects[1].height())
            );
}

void OpenXRGraphics::initialize() {
    //Make the context current
    bool isCurrent = glContext->makeCurrent(surface);

    //Set the window bounds to the minimum to fit both views in case they are asymmetrical
    window->setGeometry(QRect(QPoint(0,0),totalSize));

    //Create and link the FBO
    glFBO = new QOpenGLFramebufferObject(totalSize, QOpenGLFramebufferObject::NoAttachment, GL_TEXTURE_2D, GL_RGBA8);
    window->setRenderTarget(glFBO);

    //Start the Qt quick renderer
    quickRenderer->initialize(glContext);

    //Update the swapchain info's values
    swapInfo.width = eyeRects[0].width();
    swapInfo.height = eyeRects[0].height();
    swapInfo.sampleCount = eyeData[0].recommendedSwapchainSampleCount;

    //Do all this for both eyes
    for(int i=0; i<2; i++) {
        //Create the swapchains
        xrCreateSwapchain(*openxr->stardustSession, &swapInfo, &swapchains[i]);

        //Get the amount of swapchain images
        uint32_t swapchainLength = 0;
        xrEnumerateSwapchainImages(swapchains[i], 0, &swapchainLength, nullptr);

        assert(swapchainLength > 0);

        // Resize the swapchain-length for current eye i
        swapchainImages[i].resize(swapchainLength);
        for (uint32_t j = 0; j < swapchainLength; j++)
            swapchainImages[i][j].type = XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR;
        xrEnumerateSwapchainImages(swapchains[i], swapchainLength, &swapchainLength, reinterpret_cast<XrSwapchainImageBaseHeader*>(swapchainImages[i].data()));

        openglImages[i].resize(swapchainImages[i].size());
        for (size_t j = 0; j < swapchainImages[i].size(); j++)
            openglImages[i][j] = swapchainImages[i][j].image;
    }

    //Create a reference space relative to the iz (floor)
    xrCreateReferenceSpace(*openxr->stardustSession, &refSpaceInfo, &refSpace);

    //Initialize views vector
    views = std::vector<XrView>(2, XrView {XR_TYPE_VIEW, nullptr});

    //Make the QML engine and components and so on
    if (!qmlEngine->incubationController())
        qmlEngine->setIncubationController(window->incubationController());
}
