import QtQuick

import editor

Window {
    id: root
    width: 1280
    height: 768
    minimumWidth: 1280
    minimumHeight: 768
    visible: true

    LHEView3D {
        anchors.fill: parent

        myData: models.myData
    }

    LHEProject {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === LHEMenu.ModuleType.Project)
    }

    LHEModels {
        id: models

        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === LHEMenu.ModuleType.Models)
    }

    LHEPlaces {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === LHEMenu.ModuleType.Places)
    }

    LHECharacters {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === LHEMenu.ModuleType.Characters)
    }

    LHELinks {
        anchors.top: menu.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        enabled: (menu.selected === LHEMenu.ModuleType.Links)
    }

    LHEMenu {
        id: menu

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    LHEToolBar {
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: menu.left
        anchors.rightMargin: 10
    }
}
