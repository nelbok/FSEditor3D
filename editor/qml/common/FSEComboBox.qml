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

        // FIXME: Colors for hovered item in the popup

        palette.text: MyStyles.current.foreground.normal // Foreground popup
        palette.buttonText: MyStyles.current.foreground.normal // Foreground text
        palette.button: (enabled) ? MyStyles.current.textfield.normal : MyStyles.current.textfield.disabled // Background color
        palette.mid: MyStyles.current.textfield.normal // Button background color when popup shown
        palette.window: MyStyles.current.textfield.normal // Popup background color
        palette.dark: MyStyles.current.foreground.normal // Foreground indicator

        font.bold: MyStyles.current.normalFont.bold
        font.italic: MyStyles.current.normalFont.italic
        font.pointSize: MyStyles.current.normalFont.pointSize

        onActivated: root.activated()
    }
}
