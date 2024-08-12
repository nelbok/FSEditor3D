import QtQuick

import editor

Window {
    width: 1280
    height: 768
    minimumWidth: 1280
    minimumHeight: 768
    visible: true

    FSEView3D {
        anchors.fill: parent
        enabled: !(progress.visible || message.visible)
    }

    FSEProject {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.currentType === MySelection.Type.Project) && !(progress.visible || message.visible)
    }

    FSEModels {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.currentType === MySelection.Type.Models) && !(progress.visible || message.visible)
    }

    FSEPlaces {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.currentType === MySelection.Type.Places) && !(progress.visible || message.visible)
    }

    FSEObjects {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.currentType === MySelection.Type.Objects) && !(progress.visible || message.visible)
    }

    FSELinks {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.currentType === MySelection.Type.Links) && !(progress.visible || message.visible)
    }

    FSESettings {
        anchors.centerIn: parent

        visible: (MySelection.currentType === MySelection.Type.Settings) && !(progress.visible || message.visible)
    }

    FSEMenu {
        id: menu

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: !(progress.visible || message.visible)
    }

    FSEToolBar {
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: menu.left
        anchors.rightMargin: 10

        enabled: !(progress.visible || message.visible)
    }

    Connections {
        target: MyManager
        function onBeginFileTransaction() {
            progress.visible = true
        }
        function onEndFileTransaction(result) {
            progress.visible = false
            if (result === MyFileManager.Result.Error) {
                message.text = qsTr("An error occurred!")
                message.visible = true;
            }
        }
    }

    FSEProgressBox {
        id: progress
        anchors.centerIn: parent
        visible: false
        onClicked: MyManager.requestFileTransactionInterruption()
    }

    FSEMessageBox {
        id: message
        anchors.centerIn: parent
        visible: false
        onClicked: message.visible = false
    }
}
