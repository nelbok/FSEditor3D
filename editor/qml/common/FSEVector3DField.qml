import QtQuick
import QtQuick.Layouts

import editor

RowLayout {
    property alias name: name.text
    property alias xEnabled: posX.enabled
    property alias yEnabled: posY.enabled
    property alias zEnabled: posZ.enabled
    property vector3d value: Qt.vector3d(0, 0, 0)
    signal editingFinished(value: vector3d)

    id: root

    height: 40

    spacing: 5

    FSEText {
        id: name

        Layout.preferredWidth: 80
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

    FSEField {
        id: posX

        Layout.preferredWidth: 55

        horizontalAlignment: FSEField.AlignHCenter
        text: root.value.x.toString()

        onEditingFinished: if (acceptableInput) func.emit()
        validator: DoubleValidator{}
    }

    FSEField {
        id: posY

        Layout.preferredWidth: 55

        horizontalAlignment: FSEField.AlignHCenter
        text: root.value.y.toString()

        onEditingFinished: if (acceptableInput) func.emit()
        validator: DoubleValidator{}
    }

    FSEField {
        id: posZ

        Layout.preferredWidth: 55

        horizontalAlignment: FSEField.AlignHCenter
        text: root.value.z.toString()

        onEditingFinished: if (acceptableInput) func.emit()
        validator: DoubleValidator{}
    }
}
