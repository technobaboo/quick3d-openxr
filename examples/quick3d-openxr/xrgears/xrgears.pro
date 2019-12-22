QT += quick quick3d-private quick3d-openxr

target.path = $$[QT_INSTALL_EXAMPLES]/quick3d-openxr/xrgears
INSTALLS += target

SOURCES += \
    main.cpp

RESOURCES += \
    resources.qrc

#Inspired by Collabora's XRGears demo (https://gitlab.freedesktop.org/monado/demos/xrgears)
