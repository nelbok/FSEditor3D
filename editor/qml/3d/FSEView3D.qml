import QtQuick
import QtQuick3D

import "ModelLoader.js" as MyLoader

import editor

Item {
    property bool isCollisateur: false

    FSECollideView3D {
        anchors.fill: parent
        visible: parent.isCollisateur

        Node {
            id: fseScene

            Connections {
                target: MyPreview
                function onPreviewUpdated() {
                    MyLoader.load(MyPreview.datas)
                }
            }

            Component.onCompleted: {
                MyLoader.setScene(fseScene)
            }
        }
    }

    FSEDesignView3D {
        anchors.fill: parent
        visible: !parent.isCollisateur

        importScene: fseScene
    }
}
