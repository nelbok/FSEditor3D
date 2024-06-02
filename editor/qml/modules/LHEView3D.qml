import QtQuick
import QtQuick3D
import QtQuick3D.Helpers

import editor

// https://doc.qt.io/qt-6/qtquick3dphysics-units.html
// Qt Quick 3D Unit: cm
View3D {
    property MyModel myData: null

    id: view3D

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

    Connections {
        target: myData
        function onQmlNameUpdated() {
            if (myData.qmlName !== "")
                load(MyManager.balsam.qmlPath(myData))
            else
                clean()
        }
    }
    onMyDataChanged: {
        if (myData && myData.qmlName !== "")
            load(MyManager.balsam.qmlPath(myData))
        else
            clean()
    }

    property var cpt: null;
    property var map: null;

    function clean() {
        if (map) {
            map.destroy()
            map = null
        }
        if (cpt) {
            cpt.destroy()
            cpt = null
        }
    }

    function load(url) {
        clean()
        cpt = Qt.createComponent(url);
        if (cpt.status === Component.Ready)
            finishLoading()
        else
            cpt.statusChanged.connect(finishLoading)
    }

    function finishLoading() {
        if (cpt.status === Component.Ready) {
            map = cpt.createObject(view3D.scene);
            map.scale = Qt.vector3d(100, 100, 100)
        } else if (cpt.status === Component.Error) {
            console.log("Error while loading:" + cpt.errorString());
        } else {
            console.log("Something wrong...");
        }
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
