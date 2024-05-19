import QtQuick

import editor

LHERectangle {
    property alias text: label.text
    property bool selected: false
    signal clicked()
    width: 120
    height: 40

    border.color: {
        if (!enabled) return LHEStyle.module.border.colorDisabled
        if (mouseArea.containsMouse) return LHEStyle.module.border.colorHover
        if (selected) return LHEStyle.module.border.colorSelected;
        return LHEStyle.module.border.colorNormal
    }
    color: LHEStyle.button.normal

    Text {
        id: label

        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: (enabled) ? LHEStyle.foreground.normal : LHEStyle.foreground.disabled
        font.bold: LHEStyle.normalFont.bold
        font.italic: LHEStyle.normalFont.italic
        font.pointSize: LHEStyle.normalFont.pointSize
    }
    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true
        onClicked: (mouse)=> { if (mouse.button === Qt.LeftButton) parent.clicked() }
    }
}
