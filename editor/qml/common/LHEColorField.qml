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

    LHEText {
        id: name

        Layout.preferredWidth: 80
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
