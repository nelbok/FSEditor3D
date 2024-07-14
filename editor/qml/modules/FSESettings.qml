import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    id: root
    width: 800
    height: 600

    RowLayout {
        spacing: 5

        anchors.centerIn: root

        ColumnLayout {
            spacing: 5

            Layout.alignment: Qt.AlignTop

            FSEComboBox {
                name: qsTr("Gender")
                model: [
                    { uuid: 0, name: qsTr("Basic") },
                    { uuid: 1, name: qsTr("Dark") },
                    { uuid: 2, name: qsTr("Light") },
                ]
                currentIndex: MyStyles.index
                onActivated: MyStyles.index = currentIndex
            }
        }

        ColumnLayout {
            spacing: 5

            FSETextField {
                name: qsTr("Example A")
                value: qsTr("It is an example.")
            }

            FSESpinBox {
                name: qsTr("Example B")
                value: 42
            }

            FSEVector3DField {
                name: qsTr("Example C")
                value: Qt.vector3d(42, 42, 42)
            }
        }
    }
}
