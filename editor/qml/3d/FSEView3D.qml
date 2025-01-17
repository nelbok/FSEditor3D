import QtQuick
import QtQuick3D

import "ModelLoader.js" as MyLoader

import editor

Item {
    FSECollideView3D {
        anchors.fill: parent
        visible: MyPreview.viewMode === MyPreview.ViewMode.Collide

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
        visible: MyPreview.viewMode === MyPreview.ViewMode.Design

        importScene: fseScene
    }
}
