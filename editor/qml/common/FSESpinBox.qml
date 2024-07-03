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
        palette.text: MyStyles.current.foreground.normal
        palette.base: MyStyles.current.textfield.color // Background color
        palette.button: MyStyles.current.textfield.disabled // Background color disabled & border color
        palette.mid: MyStyles.current.textfield.disabled // Indicator color disabled
        palette.highlight: "transparent"
        font.bold: MyStyles.current.normalFont.bold
        font.italic: MyStyles.current.normalFont.italic
        font.pointSize: MyStyles.current.normalFont.pointSize

        onValueChanged: root.valueModified()
    }
}
