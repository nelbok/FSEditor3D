import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    width: 130
    height: 365

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        FSEButton {
            text: qsTr("Center on")
            enabled: !MyPreview.isGravityEnabled
            onClicked: MyPreview.centerOnCurrent()
        }

        FSEButton {
            text: qsTr("Show objects")
            selected: MyPreview.areObjectsVisible
            onClicked: MyPreview.switchObjectsVisible()
        }

        FSEButton {
            text: qsTr("Show links")
            selected: MyPreview.areLinksVisible
            onClicked: MyPreview.switchLinksVisible()
        }

        FSEButton {
            text: qsTr("Show origins")
            selected: MyPreview.areOriginsVisible
            onClicked: MyPreview.switchOriginsVisible()
        }

        FSEButton {
            text: qsTr("World mode")
            selected: MyPreview.isWorldMode
            onClicked: MyPreview.switchWorldMode()
        }

        FSEButton {
            text: qsTr("Debug mode")
            selected: MyPreview.isDebugMode
            onClicked: MyPreview.switchDebugMode()
        }

        FSEButton {
            text: qsTr("Design mode")
            selected: MyPreview.viewMode === MyPreview.ViewMode.Design
            onClicked: MyPreview.switchViewMode()
        }

        FSEButton {
            text: qsTr("Gravity")
            selected: MyPreview.isGravityEnabled
            onClicked: MyPreview.switchGravity()
        }
    }
}
