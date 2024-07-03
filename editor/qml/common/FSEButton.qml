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
        if (!enabled) return MyStyles.current.module.border.disabled
        if (mouseArea.containsMouse) return MyStyles.current.module.border.hovered
        if (selected) return MyStyles.current.module.border.selected;
        return MyStyles.current.module.border.normal
    }
    color: MyStyles.current.button.normal

    Text {
        id: label

        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: (enabled) ? MyStyles.current.foreground.normal : MyStyles.current.foreground.disabled
        font.bold: MyStyles.current.normalFont.bold
        font.italic: MyStyles.current.normalFont.italic
        font.pointSize: MyStyles.current.normalFont.pointSize
    }
    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true
        onClicked: (mouse)=> { if (mouse.button === Qt.LeftButton) parent.clicked() }
    }
}
