import QtQuick3D 1.14
import QtQuick3D.Materials 1.14

Node {
    id: scene

//    SceneEnvironment {
//        id: skybox
//        probeBrightness: 1000
//        backgroundMode: SceneEnvironment.SkyBox

//        lightProbe: Texture {
//            source: "qrc:/rooftop_night_4k.hdr"
//        }
//    }

//    Model {
//        source: "BlueGear.mesh"
//    }

    Model {
        source: "qrc:/RedGear.mesh"
        materials: PrincipledMaterial {
            lighting: PrincipledMaterial.NoLighting
            emissiveColor: "#ffffff"
        }

//        position: Qt.vector3d(0, 100, 1.65)
    }
}
