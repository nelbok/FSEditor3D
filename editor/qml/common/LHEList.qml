import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import LHEditor

ColumnLayout {
    property alias model: list.model
    signal createClicked()
    signal removeClicked(data: QtObject)
    signal duplicateClicked(data: QtObject)
    signal currentDataChanged(data: QtObject)

    id: root

    spacing: 0

    RowLayout {
        spacing: 0

        LHEMenuButton {
            text: qsTr("Add")
            width: 60
            onClicked: root.createClicked()
        }
        LHEMenuButton {
            text: qsTr("Del")
            width: 60
            onClicked: root.removeClicked(list.model[list.currentIndex])
        }
        LHEMenuButton {
            text: qsTr("Dup")
            width: 60
            onClicked: root.duplicateClicked(list.model[list.currentIndex])
        }
    }

    Rectangle {
        border.color: LHEStyle.list.border.color
        border.width: LHEStyle.list.border.width
        color: LHEStyle.list.color
        radius: LHEStyle.list.radius

        width: 180
        height: 180

        ListView {
            id: list
            anchors.fill: parent
            clip: true

            delegate: Item {
                width: list.width
                height: 30
                Text {
                    anchors.fill: parent
                    text: " " + modelData.name

                    color: LHEStyle.foreground.normal
                    font.bold: LHEStyle.normalFont.bold
                    font.italic: LHEStyle.normalFont.italic
                    font.pointSize: LHEStyle.normalFont.pointSize

                    verticalAlignment: Text.AlignVCenter
                    MouseArea {
                        anchors.fill: parent
                        preventStealing: true
                        onClicked: list.currentIndex = index
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {}
            highlight: Item {
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: LHEStyle.list.border.width

                    color: LHEStyle.list.highlight
                }
            }

            onCurrentIndexChanged: (model) ? root.currentDataChanged(model[currentIndex]) : null
            Component.onCompleted: currentIndex = -1

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: (mouse) => {
                    list.currentIndex = -1
                    mouse.accepted = false;
                }
            }
        }
    }
}