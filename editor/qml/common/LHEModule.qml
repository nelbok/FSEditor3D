import QtQuick
import QtQuick.Layouts

import LHEditor

LHERectangle {
    property alias title: title.text
    property bool selected: false

    property Item selection: null
    property Item placement: null
    property alias ppp: ppp
    property Item partA: null
    property Item partB: null

    anchors.topMargin: (selected) ? 10 : -400
    Behavior on anchors.topMargin {
        NumberAnimation { duration: 300 }
    }

    width: 1100
    height: 270

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

        color: LHEStyle.foreground.normal
        font.bold: LHEStyle.subTitleFont.bold
        font.italic: LHEStyle.subTitleFont.italic
        font.pointSize: LHEStyle.subTitleFont.pointSize
    }

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        spacing: 40

        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            border.color: "red"
            color: "transparent"

            width: 180
            height: 220

            children: (root.selection) ? root.selection : []
        }

        Rectangle {
            id: ppp
            border.color: "red"
            color: "transparent"

            width: 260
            height: 220

            children: (root.placement) ? root.placement : []
        }

        Rectangle {
            border.color: "red"
            color: "transparent"

            width: 260
            height: 220

            children: (root.partA) ? root.partA : []
        }

        Rectangle {
            border.color: "red"
            color: "transparent"

            width: 260
            height: 220

            children: (root.partB) ? root.partB : []
        }
    }
}