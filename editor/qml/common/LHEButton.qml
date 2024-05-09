import QtQuick
import QtQuick.Layouts

import LHEditor

LHERectangle {
    property alias text: label.text
    property bool selected: false
    signal clicked()
    width: 120
    height: 40

    border.color: {
        (mouseArea.containsMouse)
                ? LHEStyle.module.border.colorHover
                : (selected)
                  ? LHEStyle.module.border.colorSelected
                  : LHEStyle.module.border.colorNormal
    }
    color: LHEStyle.button.normal

    Text {
        id: label

        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: LHEStyle.foreground.normal
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
