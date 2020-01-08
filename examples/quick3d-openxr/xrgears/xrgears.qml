import QtQuick 2.12
import QtQuick3D 1.14
import QtQuick3D.Materials 1.14
import QtQuick3D.OpenXR 1.0

Node {
    id: scene

    SceneEnvironment {
        id: skybox
        probeBrightness: 1000
        backgroundMode: SceneEnvironment.SkyBox

        lightProbe: Texture {
            source: "qrc:/rooftop_night_4k.hdr"
        }

        Component.onCompleted: OpenXR.setEnvironment(skybox)
    }

//    Model {
//        source: "BlueGear.mesh"
//    }

//    Model {
//        source: "qrc:/RedGear.mesh"
//        materials: PrincipledMaterial {
//            lighting: PrincipledMaterial.NoLighting
//            emissiveColor: Qt.rgba(0,1,1,1)
//        }

//        position: Qt.vector3d(0, 100, 1.65)
//    }
}
