import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import editor

ColumnLayout {
    property alias model: list.model
    property alias currentIndex: list.currentIndex
    signal createClicked()
    signal removeClicked()
    signal duplicateClicked()
    signal itemClicked(index: int)

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
            onClicked: { root.removeClicked() }
        }
        LHEMenuButton {
            text: qsTr("Dup")
            width: 60
            onClicked: { root.duplicateClicked() }
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
                required property int index
                required property string name

                width: list.width
                height: 30
                Text {
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    text: name

                    color: LHEStyle.foreground.normal
                    font.bold: LHEStyle.normalFont.bold
                    font.italic: LHEStyle.normalFont.italic
                    font.pointSize: LHEStyle.normalFont.pointSize

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
                    anchors.margins: LHEStyle.list.border.width

                    color: LHEStyle.list.highlight
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
