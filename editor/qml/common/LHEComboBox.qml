import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import editor

RowLayout {
    property alias name: name.text
    property alias model: comboBox.model
    property alias currentIndex: comboBox.currentIndex
    signal activated()

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

    function indexOfValue(value) { return comboBox.indexOfValue(value) }
    function valueAt(index) { return comboBox.valueAt(index) }

    ComboBox {
        id: comboBox

        Layout.preferredWidth: 175

        valueRole: "uuid"
        textRole: "name"

        palette.text: LHEStyle.foreground.normal // Foreground popup
        palette.buttonText: LHEStyle.foreground.normal // Foreground text
        palette.button: (enabled) ? LHEStyle.textfield.color : LHEStyle.textfield.disabled // Background color
        palette.mid: LHEStyle.textfield.color // Background color when popup shown
        font.bold: LHEStyle.normalFont.bold
        font.italic: LHEStyle.normalFont.italic
        font.pointSize: LHEStyle.normalFont.pointSize

        onActivated: root.activated()
    }
}
