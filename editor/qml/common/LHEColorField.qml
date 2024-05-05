import QtQuick
import QtQuick.Dialogs

Item {
    property color color: "transparent"
    signal colorEdited(color: color)

    id: root
    implicitWidth: 200
    implicitHeight: 40

    Rectangle {
        anchors.fill: parent
        border.color: "black"
        border.width: 2
        color: root.color
        MouseArea {
            anchors.fill: parent
            onClicked: colorDialog.open()
        }

        ColorDialog {
            id: colorDialog
            selectedColor: root.color
            onAccepted: root.colorEdited(selectedColor)
        }
    }
}
