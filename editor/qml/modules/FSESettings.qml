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
                name: qsTr("Theme")
                model: ListModel {
                    ListElement { uuid: "basic"; name: qsTr("Basic") }
                    ListElement { uuid: "dark"; name: qsTr("Dark") }
                    ListElement { uuid: "light"; name: qsTr("Light") }
                }
                Component.onCompleted: currentIndex = indexOfValue(MyStyles.current)
                onActivated: MyStyles.current = valueAt(currentIndex)
            }

            FSEComboBox {
                name: qsTr("Language")
                model: ListModel {
                    ListElement { uuid: "en"; name: qsTr("English") }
                    ListElement { uuid: "fr"; name: qsTr("French") }
                }
                Component.onCompleted: currentIndex = indexOfValue(MyTranslations.current)
                onActivated: MyTranslations.current = valueAt(currentIndex)
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
