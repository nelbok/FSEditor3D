import QtQuick

import editor

FSERectangle {
    property alias source: image.source
    signal clicked()
    height: 40
    width: 40

    border.color: {
        if (!enabled) return FSEStyle.module.border.colorDisabled
        if (mouseArea.containsMouse) return FSEStyle.module.border.colorHover
        return FSEStyle.module.border.colorNormal
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
