import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    width: 50
    height: 50

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.style.newFile + ".svg"
            onClicked: MyPreview.centerOnCurrent()
        }
    }
}
