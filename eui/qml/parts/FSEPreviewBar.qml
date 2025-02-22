import QtQuick
import QtQuick.Layouts

import eui

FSERectangle {
    width: 130
    height: 365

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        FSEButton {
            text: qsTr("Center on")
            onClicked: MyPreview.centerOnCurrent()
        }

        FSEButton {
            text: qsTr("Show entry points")
            selected: MyPreview.areEntryPointsVisible
            onClicked: MyPreview.switchEntryPointsVisible()
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
            enabled: MyPreview.viewMode === MyPreview.ViewMode.Collide
            selected: MyPreview.isGravityEnabled
            onClicked: MyPreview.switchGravity()
        }
    }
}
