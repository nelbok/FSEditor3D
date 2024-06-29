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
        if (!enabled) return FSEStyle.module.border.colorDisabled
        if (mouseArea.containsMouse) return FSEStyle.module.border.colorHover
        if (selected) return FSEStyle.module.border.colorSelected;
        return FSEStyle.module.border.colorNormal
    }
    color: FSEStyle.button.normal

    Text {
        id: label

        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: (enabled) ? FSEStyle.foreground.normal : FSEStyle.foreground.disabled
        font.bold: FSEStyle.normalFont.bold
        font.italic: FSEStyle.normalFont.italic
        font.pointSize: FSEStyle.normalFont.pointSize
    }
    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true
        onClicked: (mouse)=> { if (mouse.button === Qt.LeftButton) parent.clicked() }
    }
}
