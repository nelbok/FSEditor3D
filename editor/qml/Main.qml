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

        myData: {
            if (models.enabled)
                return MySelection.currentModel
            if (places.enabled && MySelection.currentPlace)
                return MySelection.currentPlace.model
            if (objects.enabled && MySelection.currentObject)
                return MySelection.currentObject.model
            if (links.enabled && MySelection.currentLink)
                return MySelection.currentLink.model
            return null
        }

        enabled: !(progress.visible || message.visible)
    }

    FSEProject {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.current === MySelection.Type.Project) && !(progress.visible || message.visible)
    }

    FSEModels {
        id: models

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.current === MySelection.Type.Models) && !(progress.visible || message.visible)
    }

    FSEPlaces {
        id: places

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.current === MySelection.Type.Places) && !(progress.visible || message.visible)
    }

    FSEObjects {
        id: objects

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.current === MySelection.Type.Objects) && !(progress.visible || message.visible)
    }

    FSELinks {
        id: links

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (MySelection.current === MySelection.Type.Links) && !(progress.visible || message.visible)
    }

    FSESettings {
        id: settings

        anchors.centerIn: parent

        visible: (MySelection.current === MySelection.Type.Settings) && !(progress.visible || message.visible)
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

        onSettingsClicked: MySelection.current = (MySelection.current === MySelection.Type.Settings) ? MySelection.Type.None : MySelection.Type.Settings

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
