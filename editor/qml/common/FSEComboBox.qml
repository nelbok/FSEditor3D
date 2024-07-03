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

        palette.text: MyStyles.current.foreground.normal // Foreground popup
        palette.buttonText: MyStyles.current.foreground.normal // Foreground text
        palette.button: (enabled) ? MyStyles.current.textfield.color : MyStyles.current.textfield.disabled // Background color
        palette.mid: MyStyles.current.textfield.color // Background color when popup shown
        font.bold: MyStyles.current.normalFont.bold
        font.italic: MyStyles.current.normalFont.italic
        font.pointSize: MyStyles.current.normalFont.pointSize

        onActivated: root.activated()
    }
}
