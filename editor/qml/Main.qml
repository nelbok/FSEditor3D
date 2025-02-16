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
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Project) && !(progress.visible || message.visible)
    }

    FSEModels {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Models) && !(progress.visible || message.visible)
    }

    FSEPlaces {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Places) && !(progress.visible || message.visible)
    }

    FSEObjects {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Objects) && !(progress.visible || message.visible)
    }

    FSELinks {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Links) && !(progress.visible || message.visible)
    }

    FSEEntryPoints {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.EntryPoints) && !(progress.visible || message.visible)
    }

    FSESettings {
        anchors.centerIn: parent

        visible: (MySelection.currentType === MySelection.Type.Settings) && !(progress.visible || message.visible)
    }

    FSEMenu {
        id: menu

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: toolBar.right
        anchors.leftMargin: 10
        anchors.right: previewBar.left
        anchors.rightMargin: 10

        enabled: !(progress.visible || message.visible)
    }

    FSEToolBar {
        id: toolBar

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        enabled: !(progress.visible || message.visible)
    }

    FSEPreviewBar {
        id: previewBar

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        enabled: !(progress.visible || message.visible)
    }

    FSEProgressBox {
        id: progress
        anchors.centerIn: parent
        visible: (MyFile.status !== MyFile.Status.None && MyFile.status !== MyFile.Status.Stopped)
        onClicked: MyFile.requestFileTransactionInterruption()
    }

    Connections {
        target: MyErrors
        function onTypeUpdated() {
            message.text = MyErrors.message;
            message.visible = MyErrors.type !== MyErrors.Type.NoError
        }
    }

    Connections {
        target: MyUpdate
        function onNewVersionAvailable() {
            message.text = qsTr("A new version is available:\nVersion ") + MyUpdate.version
            message.visible = true
        }
    }

    FSEMessageBox {
        id: message
        anchors.centerIn: parent
        visible: false
        onClicked: { message.visible = false }
    }

    Component.onCompleted: {
        MyUpdate.checkForUpdates()
    }
}
