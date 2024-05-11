import QtQuick
import QtQuick.Dialogs
import QtQuick.Layouts

import editor

RowLayout {
    property alias name: name.text
    property alias color: button.color
    signal colorEdited(color: color)

    id: root

    height: 40

    spacing: 5

    Text {
        id: name

        Layout.preferredWidth: 80

        horizontalAlignment: Text.AlignRight

        color: LHEStyle.foreground.normal
        font.bold: LHEStyle.normalFont.bold
        font.italic: LHEStyle.normalFont.italic
        font.pointSize: LHEStyle.normalFont.pointSize
    }

    LHEButton {
        id: button

        Layout.preferredWidth: 175

        onClicked: dialog.open()
    }

    ColorDialog {
        id: dialog
        selectedColor: root.color
        onAccepted: root.colorEdited(selectedColor)
    }
}
