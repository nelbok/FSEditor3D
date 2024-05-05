import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    property vector2d rotation: Qt.vector3d(0, 0, 0)
    signal rotationEdited(rotation: vector3d)

    id: root
    implicitWidth: 200
    implicitHeight: 40

    RowLayout {
        id: layout
        anchors.fill: parent
        spacing: 10

        function emitEdition() {
            var v = Qt.vector2d(
                        posXZ.text,
                        posY.text
                        );
            root.rotationEdited(v);
        }

        Text {
            text: "XZ:"
        }

        TextField {
            id: posXZ
            implicitWidth: 60
            horizontalAlignment: TextField.AlignHCenter
            text: root.rotation.x.toString()
            onTextEdited: if (acceptableInput) layout.emitEdition()
            validator: DoubleValidator{}
        }

        Item {
            Layout.fillWidth: true
        }

        Text {
            text: "Y:"
        }

        TextField {
            id: posY
            implicitWidth: 60
            horizontalAlignment: TextField.AlignHCenter
            text: root.rotation.y.toString()
            onTextEdited: if (acceptableInput) layout.emitEdition()
            validator: DoubleValidator{}
        }
    }
}
