import QtQuick
import QtQuick.Layouts

import editor

RowLayout {
    property alias name: name.text
    property alias value: value.text
    property alias placeholder: value.placeholderText
    signal editingFinished()

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

    LHEField {
        id: value

        Layout.preferredWidth: 175

        onEditingFinished: if (acceptableInput) root.editingFinished()
        validator: RegularExpressionValidator{ regularExpression: /.+/ }
    }
}
