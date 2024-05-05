import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import LHEditor

Rectangle {
    property MyPlace myData: null;

    id: root
    border.color: "black"
    border.width: 2
    color: "#6666AA"
    radius: 5

    implicitHeight: layout.implicitHeight + 20
    implicitWidth: layout.implicitWidth + 20

    GridLayout {
        id: layout
        anchors.fill: parent
        anchors.margins: 10
        columns: 2

        Text {
            text: "Name:"
        }
        TextField {
            text: (root.myData) ? root.myData.name : "-"
            onEditingFinished: { if (root.myData) root.myData.name = text }
            enabled: root.myData
        }
    }
}
