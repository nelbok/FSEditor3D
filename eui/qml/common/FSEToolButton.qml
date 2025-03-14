import QtQuick

import eui

FSERectangle {
    property alias source: image.source
    signal clicked()
    height: 40
    width: 40

    border.color: {
        if (!enabled) return MyStyles.style.part.border.disabled
        if (mouseArea.containsMouse) return MyStyles.style.part.border.hovered
        return MyStyles.style.part.border.normal
    }

    Image {
        id: image
        anchors.fill: parent
        anchors.margins: 4

        mipmap: true
        fillMode: Image.PreserveAspectFit
    }
    MouseArea {
        id: mouseArea

        anchors.fill: parent

        // Avoid 3D View to catch mouse events
        preventStealing: true

        hoverEnabled: true
        onClicked: (mouse)=> { if (mouse.button === Qt.LeftButton) parent.clicked() }
    }
}
