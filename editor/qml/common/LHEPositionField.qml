import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    property vector3d position: Qt.vector3d(0, 0, 0)
    signal positionEdited(position: vector3d)

    id: root
    implicitWidth: 200
    implicitHeight: 40

    RowLayout {
        id: layout
        anchors.fill: parent
        spacing: 3

        function emitEdition() {
            var v = Qt.vector3d(
                        posX.text,
                        posY.text,
                        posZ.text
                        );
            root.positionEdited(v);
        }

        TextField {
            id: posX
            implicitWidth: 60
            horizontalAlignment: TextField.AlignHCenter
            text: root.position.x.toString()
            onTextEdited: if (acceptableInput) layout.emitEdition()
            validator: DoubleValidator{}
        }

        Rectangle {
            width: 4
            height: 3
            color: "black"
        }

        TextField {
            id: posY
            implicitWidth: 60
            horizontalAlignment: TextField.AlignHCenter
            text: root.position.y.toString()
            onTextEdited: if (acceptableInput) layout.emitEdition()
            validator: DoubleValidator{}
        }

        Rectangle {
            width: 4
            height: 3
            color: "black"
        }

        TextField {
            id: posZ
            implicitWidth: 60
            horizontalAlignment: TextField.AlignHCenter
            text: root.position.z.toString()
            onTextEdited: if (acceptableInput) layout.emitEdition()
            validator: DoubleValidator{}
        }
    }
}
