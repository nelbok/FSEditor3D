import QtQuick

import editor

Rectangle {
    border.color: MyStyles.style.module.border.normal
    border.width: MyStyles.style.module.border.width
    color: MyStyles.style.module.normal
    radius: MyStyles.style.module.radius

    MouseArea {
        anchors.fill: parent

        // Avoid 3D View to catch mouse events
        preventStealing: true
    }
}
