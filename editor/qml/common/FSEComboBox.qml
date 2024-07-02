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

        palette.text: MyManager.style.foreground.normal // Foreground popup
        palette.buttonText: MyManager.style.foreground.normal // Foreground text
        palette.button: (enabled) ? MyManager.style.textfield.color : MyManager.style.textfield.disabled // Background color
        palette.mid: MyManager.style.textfield.color // Background color when popup shown
        font.bold: MyManager.style.normalFont.bold
        font.italic: MyManager.style.normalFont.italic
        font.pointSize: MyManager.style.normalFont.pointSize

        onActivated: root.activated()
    }
}
