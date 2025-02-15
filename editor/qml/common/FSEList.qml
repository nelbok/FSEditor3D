import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import editor

ColumnLayout {
    property alias model: mng.model
    property alias currentData: mng.currentData
    signal activated()

    signal createClicked()
    signal removeClicked()
    signal duplicateClicked()

    id: root

    spacing: 0
    anchors.fill: parent

    MySelectionWrapper {
        id: mng
        currentData: root.currentData
        onCurrentUpdated: { root.activated() }
    }

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

            enabled: mng.currentData && !mng.currentData.hasRef
        }
        FSEMenuButton {
            id: duplicate
            text: qsTr("Dup")
            width: 60
            onClicked: { root.duplicateClicked() }

            enabled: mng.currentData
        }
    }

    Rectangle {
        border.color: MyStyles.style.list.border.normal
        border.width: MyStyles.style.list.border.width
        color: MyStyles.style.list.normal
        radius: MyStyles.style.list.radius

        Layout.preferredWidth: 180
        Layout.fillHeight: true

        ListView {
            id: list
            anchors.fill: parent
            clip: true

            model: mng.model
            currentIndex: mng.currentIndex

            delegate: Item {
                required property int index
                required property string name

                width: list.width
                height: 30
                Text {
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    text: name

                    color: MyStyles.style.foreground.normal
                    font.bold: MyStyles.style.normalFont.bold
                    font.italic: MyStyles.style.normalFont.italic
                    font.pointSize: MyStyles.style.normalFont.pointSize

                    verticalAlignment: Text.AlignVCenter
                    MouseArea {
                        anchors.fill: parent
                        preventStealing: true
                        onClicked: { mng.currentIndex = index }
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {}
            highlight: Item {
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: MyStyles.style.list.border.width

                    color: MyStyles.style.list.selected
                }
            }

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: (mouse) => {
                               mng.currentIndex = -1
                               mouse.accepted = false
                           }
            }
        }
    }
}
