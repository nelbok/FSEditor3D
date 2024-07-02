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
        palette.text: MyManager.style.foreground.normal
        palette.base: MyManager.style.textfield.color // Background color
        palette.button: MyManager.style.textfield.disabled // Background color disabled & border color
        palette.mid: MyManager.style.textfield.disabled // Indicator color disabled
        palette.highlight: "transparent"
        font.bold: MyManager.style.normalFont.bold
        font.italic: MyManager.style.normalFont.italic
        font.pointSize: MyManager.style.normalFont.pointSize

        onValueChanged: root.valueModified()
    }
}
