import QtQuick

import editor

Rectangle {
    border.color: MyStyles.style.part.border.normal
    border.width: MyStyles.style.part.border.width
    color: MyStyles.style.part.normal
    radius: MyStyles.style.part.radius

    MouseArea {
        anchors.fill: parent

        // Avoid 3D View to catch mouse events
        preventStealing: true
    }
}
