import QtQuick

import editor

Window {
    id: root
    width: 1280
    height: 768
    minimumWidth: 1280
    minimumHeight: 768
    visible: true

    FSEView3D {
        anchors.fill: parent

        myData: {
            if (models.enabled)
                return models.myData
            if (places.enabled && places.myData)
                return places.myData.model
            if (characters.enabled && characters.myData)
                return characters.myData.model
            if (links.enabled && links.myData)
                return links.myData.model
            return null
        }

        enabled: !(progress.visible || message.visible)
    }

    FSEProject {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Project) && !(progress.visible || message.visible)
    }

    FSEModels {
        id: models

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Models) && !(progress.visible || message.visible)
    }

    FSEPlaces {
        id: places

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Places) && !(progress.visible || message.visible)
    }

    FSECharacters {
        id: characters

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Characters) && !(progress.visible || message.visible)
    }

    FSELinks {
        id: links

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Links) && !(progress.visible || message.visible)
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
