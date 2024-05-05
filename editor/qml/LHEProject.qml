import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import LHEditor

Rectangle {
    property MyProject myData: null;
    signal currentPlaceChanged(place: MyPlace)

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
        Text {
            text: "Default place:"
        }
        ComboBox {
            textRole: "name"
            model: (root.myData) ? root.myData.places : null
            currentIndex: {
                if (root.myData)
                    for(var i in root.myData.places)
                        if (root.myData.places[i].uuid === root.myData.defaultPlace.uuid)
                            return i;
                return -1
            }
            onCurrentIndexChanged: {
                var value = valueAt(currentIndex)
                if (root.myData && value)
                    root.myData.defaultPlace = value
            }
            enabled: root.myData
        }
        Text {
            text: "Places:"
        }
        RowLayout {
            implicitWidth: 200
            spacing: 10

            Button {
                implicitWidth: 60
                text: "+"
                onClicked: if (root.myData) root.myData.createPlace();
                enabled: root.myData
            }

            Button {
                implicitWidth: 60
                text: "-"
                onClicked: if (root.myData && list.model[list.currentIndex]) root.myData.removePlace(list.model[list.currentIndex])
                enabled: root.myData
            }

            Button {
                implicitWidth: 60
                text: "*"
                onClicked: if (root.myData && list.model[list.currentIndex]) root.myData.duplicatePlace(list.model[list.currentIndex])
                enabled: root.myData
            }
        }
        Rectangle {
            Layout.columnSpan: 2
            Layout.minimumHeight: 200
            Layout.fillWidth: true

            border.color: "black"
            border.width: 1
            color: "transparent"

            ListView {
                id: list
                anchors.fill: parent
                clip: true

                model: (root.myData) ? root.myData.places : null
                delegate: Item {
                    width: list.width
                    height: 40
                    Text {
                        anchors.fill: parent
                        text: " " + modelData.name
                        verticalAlignment: Text.AlignVCenter
                        MouseArea {
                            anchors.fill: parent
                            onClicked: list.currentIndex = index
                        }
                    }
                }

                ScrollBar.vertical: ScrollBar {}
                highlight: Rectangle { color: "#CCCCCC" }

                onCurrentIndexChanged: root.currentPlaceChanged(model[currentIndex])
                Component.onCompleted: currentIndex = -1

                enabled: root.myData
            }
        }
    }
}
