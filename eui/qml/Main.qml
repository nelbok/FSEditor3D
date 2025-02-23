import QtQuick

import eui

Window {
    width: 1280
    height: 768
    minimumWidth: 1280
    minimumHeight: 768
    visible: true

    FSEView3D {
        anchors.fill: parent
        enabled: MyInterface.isInterfaceEnabled
    }

    FSEProject {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Project) && MyInterface.isInterfaceEnabled
    }

    FSEModels {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Models) && MyInterface.isInterfaceEnabled
    }

    FSEPlaces {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Places) && MyInterface.isInterfaceEnabled
    }

    FSEObjects {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Objects) && MyInterface.isInterfaceEnabled
    }

    FSELinks {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.Links) && MyInterface.isInterfaceEnabled
    }

    FSEEntryPoints {
        anchors.top: menu.bottom
        anchors.left: menu.left
        anchors.right: menu.right

        enabled: (MySelection.currentType === MySelection.Type.EntryPoints) && MyInterface.isInterfaceEnabled
    }

    FSESettings {
        anchors.centerIn: parent

        visible: (MySelection.currentType === MySelection.Type.Settings) && MyInterface.isInterfaceEnabled
    }

    FSEMenu {
        id: menu

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: toolBar.right
        anchors.leftMargin: 10
        anchors.right: previewBar.left
        anchors.rightMargin: 10

        enabled: MyInterface.isInterfaceEnabled
    }

    FSEToolBar {
        id: toolBar

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        enabled: MyInterface.isInterfaceEnabled
    }

    FSEPreviewBar {
        id: previewBar

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        enabled: MyInterface.isInterfaceEnabled
    }

    FSEIManager {
        anchors.fill: parent
    }

    onClosing: (close) => {
                   close.accepted = false
                   MyInterface.quit()
               }
}
