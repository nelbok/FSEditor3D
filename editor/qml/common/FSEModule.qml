import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    property alias title: title.text

    property Item selection: null
    property Item placement: null
    property Item partA: null
    property Item partB: null

    anchors.topMargin: (enabled) ? 10 : -400
    Behavior on anchors.topMargin {
        NumberAnimation { duration: 300 }
    }

    width: 1100
    height: 270

    MouseArea {
        anchors.fill: parent
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

        color: MyStyles.current.foreground.normal
        font.bold: MyStyles.current.subTitleFont.bold
        font.italic: MyStyles.current.subTitleFont.italic
        font.pointSize: MyStyles.current.subTitleFont.pointSize
    }

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        spacing: 40

        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            width: 180
            height: 220

            children: (root.selection) ? root.selection : []
        }

        Item {
            width: 260
            height: 220

            children: (root.placement) ? root.placement : []
        }

        Item {
            width: 260
            height: 220

            children: (root.partA) ? root.partA : []
        }

        Item {
            width: 260
            height: 220

            children: (root.partB) ? root.partB : []
        }
    }
}
