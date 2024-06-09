import QtQuick

import editor

LHERectangle {
    signal clicked

    id: root

    height: 180
    width: 130

    Item {
        id: container

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        height: 130
        width: 130

        Repeater {
            model: [0, 45, 90, 135, 180, 225, 270, 315]
            delegate: Item {
                anchors.centerIn: container

                RotationAnimation on rotation {
                    loops: Animation.Infinite
                    from: 0 + modelData
                    to: 360 + modelData
                    duration: 2000
                    running: root.visible
                }

                LHERectangle {
                    x: 25
                    y: -8
                    width: 16
                    height: 16
                    radius: 16
                }
            }
        }
    }

    LHEButton {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        text: qsTr("Cancel")

        onClicked: root.clicked()
    }
}
