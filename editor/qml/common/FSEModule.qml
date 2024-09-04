import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    property alias title: title.text

    property alias selection: selection.children
    property alias entity: entity.children
    property alias partA: partA.children
    property alias partB: partB.children

    anchors.topMargin: (enabled) ? 10 : -400
    Behavior on anchors.topMargin {
        NumberAnimation { duration: 300 }
    }

    width: 1100
    height: 270

    MouseArea {
        anchors.fill: parent

        // Avoid 3D View to catch mouse events
        preventStealing: true

        onClicked: {
            // For Shortcut
            parent.focus = true
            parent.focus = false
        }
    }

    Text {
        id: title

        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10

        width: 180
        height: 30

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        color: MyStyles.style.foreground.normal
        font.bold: MyStyles.style.subTitleFont.bold
        font.italic: MyStyles.style.subTitleFont.italic
        font.pointSize: MyStyles.style.subTitleFont.pointSize
    }

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        spacing: 40

        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            id: selection

            width: 180
            height: 220
        }

        Item {
            id: entity

            width: 260
            height: 220
        }

        Item {
            id: partA

            width: 260
            height: 220
        }

        Item {
            id: partB

            width: 260
            height: 220
        }
    }
}
