import QtQuick
import QtQuick.Layouts

import LHEditor

RowLayout {
    property alias name: name.text
    property vector3d value: Qt.vector3d(0, 0, 0)
    signal editingFinished(value: vector3d)

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

    QtObject {
        id: func
        function emit() {
            var v = Qt.vector3d(
                        posX.text,
                        posY.text,
                        posZ.text
                        );
            root.editingFinished(v);
        }
    }

    LHEField {
        id: posX

        Layout.preferredWidth: 55

        horizontalAlignment: LHEField.AlignHCenter
        text: root.value.x.toString()

        onEditingFinished: if (acceptableInput) func.emit()
        validator: DoubleValidator{}
    }

    LHEField {
        id: posY

        Layout.preferredWidth: 55

        horizontalAlignment: LHEField.AlignHCenter
        text: root.value.y.toString()

        onEditingFinished: if (acceptableInput) func.emit()
        validator: DoubleValidator{}
    }

    LHEField {
        id: posZ

        Layout.preferredWidth: 55

        horizontalAlignment: LHEField.AlignHCenter
        text: root.value.z.toString()

        onEditingFinished: if (acceptableInput) func.emit()
        validator: DoubleValidator{}
    }
}
