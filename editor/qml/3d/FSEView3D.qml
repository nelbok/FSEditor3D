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
        position: Qt.vector3d(0, 800, 1000)
        eulerRotation.x: -30
    }
    WasdController {
        controlledObject: camera
    }

    Connections {
        target: MyPreview
        function onPreviewUpdated() {
            var model = MyPreview.mainModel
            if (model && model.qmlName !== "")
                MyLoader.load(MyManager.balsam.qmlPath(model), MyPreview.mainGeometry)
            else
                MyLoader.clean()
        }
    }

    Component.onCompleted: {
        MyLoader.setScene(view3D.scene)
        MyLoader.init()
    }
}
