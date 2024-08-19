import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

import "ModelLoader.js" as MyLoader

import editor

// https://doc.qt.io/qt-6/qtquick3dphysics-units.html
// Qt Quick 3D Unit: cm Angle: degree
View3D {
    id: view3D

    environment: SceneEnvironment {
        clearColor: "skyblue"
        backgroundMode: SceneEnvironment.Color

        InfiniteGrid {
            gridInterval: 100 // 1meter
        }
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

        position: MyPreview.cameraPosition
        onPositionChanged: { MyPreview.cameraPosition = position }

        eulerRotation: MyPreview.cameraRotation
        onEulerRotationChanged: { MyPreview.cameraRotation = eulerRotation }
    }
    WasdController {
        controlledObject: camera
    }

    Connections {
        target: MyPreview
        function onCameraPositionUpdated() {
            camera.position = MyPreview.cameraPosition
        }
        function onCameraRotationUpdated() {
            camera.eulerRotation = MyPreview.cameraRotation
        }
        function onPreviewUpdated() {
            MyLoader.load(MyPreview.datas)
        }
    }

    Component.onCompleted: {
        MyLoader.setScene(view3D.scene)
    }
}
