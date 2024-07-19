import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import editor

RowLayout {
    property alias name: name.text
    property alias from: spinBox.from
    property alias to: spinBox.to
    property alias value: spinBox.value
    signal valueModified()

    id: root

    height: 40

    spacing: 5

    FSEText {
        id: name

        Layout.preferredWidth: 80
    }

    SpinBox {
        id: spinBox
        Layout.preferredWidth: 175

        editable: true

        // FIXME: Colors for indicator

        palette.text: MyStyles.style.foreground.normal // Foreground text
        palette.base: MyStyles.style.textfield.normal // Background color
        palette.button: MyStyles.style.textfield.disabled // Background color disabled & border color
        palette.buttonText: MyStyles.style.foreground.normal // Indicator color enabled
        palette.mid: MyStyles.style.textfield.disabled // Indicator color disabled
        palette.highlight: MyStyles.style.textfield.border.selected // Border color

        font.bold: MyStyles.style.normalFont.bold
        font.italic: MyStyles.style.normalFont.italic
        font.pointSize: MyStyles.style.normalFont.pointSize

        onValueChanged: root.valueModified()
    }
}
