import QtQuick

import editor

FSERectangle {
    property alias source: image.source
    signal clicked()
    height: 40
    width: 40

    border.color: {
        if (!enabled) return MyManager.style.module.border.disabled
        if (mouseArea.containsMouse) return MyManager.style.module.border.hovered
        return MyManager.style.module.border.normal
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

        hoverEnabled: true
        onClicked: (mouse)=> { if (mouse.button === Qt.LeftButton) parent.clicked() }
    }
}
