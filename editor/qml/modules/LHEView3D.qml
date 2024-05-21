import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

// https://doc.qt.io/qt-6/qtquick3dphysics-units.html
// Qt Quick 3D Unit: cm
View3D {
    environment: SceneEnvironment {
        clearColor: "skyblue"
        backgroundMode: SceneEnvironment.Color
    }

    // A light like the sun
    DirectionalLight {
        eulerRotation.x: -30
        eulerRotation.y: -70
        castsShadow: true
        shadowMapQuality: Light.ShadowMapQualityVeryHigh
    }

    // Camera with its controller to make it easy to move around the scene
    PerspectiveCamera {
        id: camera
        position: Qt.vector3d(0, 800, 1000)
        eulerRotation.x: -30
    }
    WasdController {
        controlledObject: camera
    }

    Model {
        id: myDebug
        visible: true
        position: Qt.vector3d(0, -100, 0)
        scale: Qt.vector3d(10,1,10)
        source: "#Cube"
        materials: DefaultMaterial {
            diffuseColor: "green"
        }
    }
}
