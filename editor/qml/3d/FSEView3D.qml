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

            Repeater3D {
                model: MyPreview.entryPointDatas
                delegate: Model {
                    position.x: modelData.offset.x + modelData.entryPoint.position.x
                    position.y: modelData.offset.y + modelData.entryPoint.position.y
                    position.z: modelData.offset.z + modelData.entryPoint.position.z
                    eulerRotation.y: modelData.entryPoint.rotation

                    eulerRotation.x: -90

                    source: "#Cone"
                    materials: DefaultMaterial {
                        diffuseColor: MyStyles.style.part.normal
                    }
                }
            }

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
