#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>

#include <Quick3DOpenXR/QOpenXRApplication>

#include <private/qqmlglobal_p.h>

QT_BEGIN_NAMESPACE

class Quick3DOpenXRPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override
    {
        qmlRegisterUncreatableType<QOpenXRApplication>("QtQuick3D.OpenXR", 1, 0, "OpenXR", "Is a QML singleton");

//        qmlRegisterModule("QtQuick3D.OpenXR", 1, QT_VERSION_MINOR);
    }
};

QT_END_NAMESPACE

#include "plugin.moc"
