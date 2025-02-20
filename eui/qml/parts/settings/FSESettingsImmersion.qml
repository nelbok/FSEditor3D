import QtQuick
import QtQuick.Layouts

import eui

RowLayout {
    spacing: 5

    ColumnLayout {
        spacing: 5

        Layout.alignment: Qt.AlignTop

        FSESpinBox {
            name: qsTr("Person height")
            from: 110
            to: 300
            value: MyPreview.height
            onValueModified: () => { MyPreview.height = value }
        }
    }
}
