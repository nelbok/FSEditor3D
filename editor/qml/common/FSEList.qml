import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import editor

ColumnLayout {
    property alias model: list.model
    property alias currentIndex: list.currentIndex
    property alias createEnabled: create.enabled
    property alias removeEnabled: remove.enabled
    property alias duplicateEnabled: duplicate.enabled

    signal createClicked()
    signal removeClicked()
    signal duplicateClicked()
    signal itemClicked(index: int)

    id: root

    spacing: 0

    RowLayout {
        spacing: 0

        FSEMenuButton {
            id: create
            text: qsTr("Add")
            width: 60
            onClicked: root.createClicked()
        }
        FSEMenuButton {
            id: remove
            text: qsTr("Del")
            width: 60
            onClicked: { root.removeClicked() }
        }
        FSEMenuButton {
            id: duplicate
            text: qsTr("Dup")
            width: 60
            onClicked: { root.duplicateClicked() }
        }
    }

    Rectangle {
        border.color: MyStyles.current.list.border.normal
        border.width: MyStyles.current.list.border.width
        color: MyStyles.current.list.normal
        radius: MyStyles.current.list.radius

        width: 180
        height: 180

        ListView {
            id: list
            anchors.fill: parent
            clip: true

            delegate: Item {
                required property int index
                required property string name

                width: list.width
                height: 30
                Text {
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    text: name

                    color: MyStyles.current.foreground.normal
                    font.bold: MyStyles.current.normalFont.bold
                    font.italic: MyStyles.current.normalFont.italic
                    font.pointSize: MyStyles.current.normalFont.pointSize

                    verticalAlignment: Text.AlignVCenter
                    MouseArea {
                        anchors.fill: parent
                        preventStealing: true
                        onClicked: { root.itemClicked(index) }
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {}
            highlight: Item {
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: MyStyles.current.list.border.width

                    color: MyStyles.current.list.selected
                }
            }

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: (mouse) => {
                               root.itemClicked(-1)
                               mouse.accepted = false
                           }
            }
        }
    }
}
