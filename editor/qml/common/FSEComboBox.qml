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

    FSEText {
        id: name

        Layout.preferredWidth: 80
    }

    function indexOfValue(value) { return comboBox.indexOfValue(value) }
    function valueAt(index) { return comboBox.valueAt(index) }

    ComboBox {
        id: comboBox

        Layout.preferredWidth: 175

        valueRole: "uuid"
        textRole: "name"

        palette.text: FSEStyle.foreground.normal // Foreground popup
        palette.buttonText: FSEStyle.foreground.normal // Foreground text
        palette.button: (enabled) ? FSEStyle.textfield.color : FSEStyle.textfield.disabled // Background color
        palette.mid: FSEStyle.textfield.color // Background color when popup shown
        font.bold: FSEStyle.normalFont.bold
        font.italic: FSEStyle.normalFont.italic
        font.pointSize: FSEStyle.normalFont.pointSize

        onActivated: root.activated()
    }
}
