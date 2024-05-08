import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import LHEditor

ColumnLayout {
    property alias model: list.model
    signal currentDataChanged(data: QtObject)

    id: root

    spacing: 0

    RowLayout {
        spacing: 0

        LHEMenuButton {
            text: qsTr("Add")
            width: 60
        }
        LHEMenuButton {
            text: qsTr("Del")
            width: 60
        }
        LHEMenuButton {
            text: qsTr("Dup")
            width: 60
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

                    font.bold: LHEStyle.normalFont.bold
                    font.italic: LHEStyle.normalFont.italic
                    font.pointSize: LHEStyle.normalFont.pointSize

                    verticalAlignment: Text.AlignVCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: list.currentIndex = index
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {}
            highlight: Item {
                Rectangle {
                    anchors.fill: parent
                    anchors.leftMargin: LHEStyle.list.border.width
                    anchors.rightMargin: LHEStyle.list.border.width

                    color: LHEStyle.list.highlight
                }
            }

            onCurrentIndexChanged: (model) ? root.currentDataChanged(model[currentIndex]) : null
            Component.onCompleted: currentIndex = -1
        }
    }
}
