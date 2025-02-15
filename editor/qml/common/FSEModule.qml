import QtQuick

import editor

FSERectangle {
    property alias selection: selection.children
    property alias entity: entity.children
    property alias partA: partA.children
    property alias partB: partB.children

    id: root

    anchors.topMargin: (enabled) ? 10 : -400
    Behavior on anchors.topMargin {
        NumberAnimation { duration: 300 }
    }

    height: 240

    QtObject {
        id: data

        property int defaultMargin: 10
        property int maxSpacing: 120
        property int margin: {
            if (data.spacing < data.maxSpacing)
                return data.defaultMargin
            return (root.width - data.spacing * 3 - entity.width - selection.width - partA.width - partB.width) / 2
        }

        property int spacing: {
            var spacing = (root.width - data.defaultMargin * 2 - entity.width - selection.width - partA.width - partB.width) / 3
            if (spacing > data.maxSpacing)
                return data.maxSpacing
            return spacing
        }
    }

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

    Item {
        id: selection

        anchors.left: parent.left
        anchors.leftMargin: data.margin
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        width: 180
    }

    Item {
        id: entity

        anchors.left: selection.right
        anchors.leftMargin: data.spacing
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        width: 260
    }

    Item {
        id: partA

        anchors.left: entity.right
        anchors.leftMargin: data.spacing
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        width: 260
    }

    Item {
        id: partB

        anchors.left: partA.right
        anchors.leftMargin: data.spacing
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        width: 260
    }
}
