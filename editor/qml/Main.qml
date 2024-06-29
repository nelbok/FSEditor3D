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
    }

    FSEProject {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Project)
    }

    FSEModels {
        id: models

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Models)
    }

    FSEPlaces {
        id: places

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Places)
    }

    FSECharacters {
        id: characters

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Characters)
    }

    FSELinks {
        id: links

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === FSEMenu.ModuleType.Links)
    }

    FSEMenu {
        id: menu

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    FSEToolBar {
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: menu.left
        anchors.rightMargin: 10
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
