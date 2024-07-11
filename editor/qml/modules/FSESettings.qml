import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    id: root
    width: 800
    height: 600

    ColumnLayout {
        spacing: 5

        anchors.centerIn: root

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
}
