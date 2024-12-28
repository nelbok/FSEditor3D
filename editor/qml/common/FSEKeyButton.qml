import QtQuick

import editor

FSERectangle {
    property alias text: label.text
    signal keyPressed(key: int)
    width: 120
    height: 40

    border.color: {
        if (!enabled) return MyStyles.style.part.border.disabled
        if (mouseArea.containsMouse) return MyStyles.style.part.border.hovered
        if (activeFocus) return MyStyles.style.part.border.selected;
        return MyStyles.style.part.border.normal
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
        onClicked: (mouse)=> { if (mouse.button === Qt.LeftButton) parent.focus=true }
    }

    Keys.onReleased: (event)=> {
                         keyPressed(event.key) // + event.modifiers
                         focus = false
                     }
}
