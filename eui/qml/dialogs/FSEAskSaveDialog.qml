import QtQuick

import eui

FSERectangle {
    signal saveClicked
    signal discardClicked
    signal cancelClicked

    id: root

    height: 150
    width: 480

    FSEText {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        text: qsTr("Do you want to save your project?")

        height: 80
    }

    FSEButton {
        id: saveBtn
        anchors.right: discardBtn.left
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        text: qsTr("Save")

        onClicked: root.saveClicked()
    }

    FSEButton {
        id: discardBtn
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        text: qsTr("Discard")

        onClicked: root.discardClicked()
    }

    FSEButton {
        id: cancelBtn
        anchors.left: discardBtn.right
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        text: qsTr("Cancel")

        onClicked: root.cancelClicked()
    }
}
