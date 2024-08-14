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

        valueRole: "value"
        textRole: "name"

        // FIXME: Colors for hovered item in the popup

        palette.text: MyStyles.style.foreground.normal // Foreground popup
        palette.buttonText: MyStyles.style.foreground.normal // Foreground text
        palette.button: (enabled) ? MyStyles.style.textfield.normal : MyStyles.style.textfield.disabled // Background color
        palette.mid: MyStyles.style.textfield.normal // Button background color when popup shown
        palette.window: MyStyles.style.textfield.normal // Popup background color
        palette.dark: MyStyles.style.foreground.normal // Foreground indicator

        font.bold: MyStyles.style.normalFont.bold
        font.italic: MyStyles.style.normalFont.italic
        font.pointSize: MyStyles.style.normalFont.pointSize

        onActivated: root.activated()
    }
}
