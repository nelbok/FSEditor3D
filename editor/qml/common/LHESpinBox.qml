import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import LHEditor

RowLayout {
    property alias name: name.text
    property alias from: spinBox.from
    property alias to: spinBox.to
    property alias value: spinBox.value
    signal valueModified()

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

    SpinBox {
        id: spinBox
        Layout.preferredWidth: 175

        editable: true
        palette.text: LHEStyle.foreground.normal
        palette.base: LHEStyle.textfield.color // Background color
        palette.button: LHEStyle.textfield.disabled // Background color disabled & border color
        palette.mid: LHEStyle.textfield.disabled // Indicator color disabled
        font.bold: LHEStyle.normalFont.bold
        font.italic: LHEStyle.normalFont.italic
        font.pointSize: LHEStyle.normalFont.pointSize

        onValueChanged: root.valueModified()
    }
}
