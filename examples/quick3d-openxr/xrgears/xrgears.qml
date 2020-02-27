import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick3D.Materials 1.15
import QtQuick3D.Helpers 1.15
import QtQuick3D.OpenXR 1.0

Node {
    id: scene

    SceneEnvironment {
        id: skybox
        backgroundMode: SceneEnvironment.Color
        clearColor: "#444"

        antialiasingMode: SceneEnvironment.MSAA
        antialiasingQuality: SceneEnvironment.Medium

        Component.onCompleted: OpenXR.setEnvironment(skybox)
    }

    Node {
        id:gears
        position: Qt.vector3d(-0.5, 1.15, 7)
        eulerRotation: Qt.vector3d(-90, 0, 0)
        scale: Qt.vector3d(0.5, 0.5, 0.5)

        property real gearTurn: 0

        RotationAnimation on gearTurn {
            duration: 5000
            loops: Animation.Infinite
            from: 0
            to: 359
            direction: RotationAnimation.Clockwise
            running: true
        }

        PointLight {
            color: "white"
//            brightness: 1
//            ambientColor: "white"
            linearFade: 5

            position: Qt.vector3d(0.5, 3, 0.5)
        }

        Model {
            id: redGear
            source: "qrc:/RedGear.mesh"
            materials: GearMaterial {
                diffuseColor: "#f00"
            }

            eulerRotation: Qt.vector3d(0, parent.gearTurn, 0)
        }

        Model {
            id: greenGear
            source: "qrc:/GreenGear.mesh"
            materials: GearMaterial {
                diffuseColor: "#0f0"
            }

            position: Qt.vector3d(3, 0, 0)
            eulerRotation: Qt.vector3d(0, -parent.gearTurn*2, 0)
        }

        Model {
            id: blueGear
            source: "qrc:/BlueGear.mesh"
            materials: GearMaterial {
                diffuseColor: "#00f"
            }

            position: Qt.vector3d(0, 0, 3)
            eulerRotation: Qt.vector3d(0, -parent.gearTurn*2, 0)
        }
    }

    AxisHelper {
        enableAxisLines: false
        enableXZGrid: true
        gridColor: "#ccc"
        gridOpacity: 1
        scale: Qt.vector3d(0.01, 0.01, 0.01)
    }
}
