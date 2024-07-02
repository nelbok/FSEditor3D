import QtQuick

import editor

FSERectangle {
    property alias text: label.text
    property alias elide: label.elide
    property bool selected: false
    signal clicked()
    width: 120
    height: 40

    border.color: {
        if (!enabled) return MyManager.style.module.border.disabled
        if (mouseArea.containsMouse) return MyManager.style.module.border.hovered
        if (selected) return MyManager.style.module.border.selected;
        return MyManager.style.module.border.normal
    }
    color: MyManager.style.button.normal

    Text {
        id: label

        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: (enabled) ? MyManager.style.foreground.normal : MyManager.style.foreground.disabled
        font.bold: MyManager.style.normalFont.bold
        font.italic: MyManager.style.normalFont.italic
        font.pointSize: MyManager.style.normalFont.pointSize
    }
    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true
        onClicked: (mouse)=> { if (mouse.button === Qt.LeftButton) parent.clicked() }
    }
}
