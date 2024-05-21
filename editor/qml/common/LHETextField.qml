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

    LHEText {
        id: name

        Layout.preferredWidth: 80
    }

    LHEField {
        id: value

        Layout.preferredWidth: 175

        onEditingFinished: {
            if (acceptableInput) {
                root.editingFinished()
                focus = false
            }
        }
        validator: RegularExpressionValidator{ regularExpression: /.+/ }
    }
}
