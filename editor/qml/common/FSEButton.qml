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
        if (!enabled) return MyStyles.style.module.border.disabled
        if (mouseArea.containsMouse) return MyStyles.style.module.border.hovered
        if (selected) return MyStyles.style.module.border.selected;
        return MyStyles.style.module.border.normal
    }
    color: MyStyles.style.button.normal

    Text {
        id: label

        anchors.fill: parent
        anchors.leftMargin: 5
        anchors.rightMargin: 5

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideMiddle

        color: (enabled) ? MyStyles.style.foreground.normal : MyStyles.style.foreground.disabled
        font.bold: MyStyles.style.normalFont.bold
        font.italic: MyStyles.style.normalFont.italic
        font.pointSize: MyStyles.style.normalFont.pointSize
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
