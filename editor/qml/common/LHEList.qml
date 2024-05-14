import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import editor

ColumnLayout {
    property alias model: myModel.model
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
            onClicked: { if (myModel.currentData) root.removeClicked(myModel.currentData) }
        }
        LHEMenuButton {
            text: qsTr("Dup")
            width: 60
            onClicked: { if (myModel.currentData) root.duplicateClicked(myModel.currentData) }
        }
    }

    Rectangle {
        border.color: LHEStyle.list.border.color
        border.width: LHEStyle.list.border.width
        color: LHEStyle.list.color
        radius: LHEStyle.list.radius

        width: 180
        height: 180

        MyEntityModel {
            id: myModel
            onCurrentDataUpdated: { root.currentDataChanged(myModel.currentData) }
        }

        ListView {
            id: list
            anchors.fill: parent
            clip: true

            model: myModel
            currentIndex: myModel.currentIndex

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
                        onClicked: { myModel.currentIndex = index }
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
                    myModel.currentIndex = -1
                    mouse.accepted = false;
                }
            }
        }
    }
}
