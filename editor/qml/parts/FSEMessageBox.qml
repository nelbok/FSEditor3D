import QtQuick

import editor

FSERectangle {
    property alias text: content.text
    signal clicked

    id: root

    height: 150
    width: 480

    FSEText {
        id: content

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap

        height: 80
    }

    FSEButton {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        text: qsTr("Ok")

        onClicked: root.clicked()
    }
}
