QT += quick quick3d-private quick3d-openxr

target.path = $$[QT_INSTALL_EXAMPLES]/quick3d-openxr/xrgears
INSTALLS += target

RESOURCES += \
    resources.qrc

SOURCES += \
    main.cpp

#Inspired by Collabora's XRGears demo (https://gitlab.freedesktop.org/monado/demos/xrgears)
