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
        palette.text: FSEStyle.foreground.normal
        palette.base: FSEStyle.textfield.color // Background color
        palette.button: FSEStyle.textfield.disabled // Background color disabled & border color
        palette.mid: FSEStyle.textfield.disabled // Indicator color disabled
        palette.highlight: "transparent"
        font.bold: FSEStyle.normalFont.bold
        font.italic: FSEStyle.normalFont.italic
        font.pointSize: FSEStyle.normalFont.pointSize

        onValueChanged: root.valueModified()
    }
}
