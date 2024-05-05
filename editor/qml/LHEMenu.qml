import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Dialogs

import LHEditor

Rectangle {
    property MyProject myData: null;

    id: root
    border.color: "black"
    border.width: 2
    color: "#6666AA"
    radius: 5

    implicitHeight: layout.implicitHeight + 20
    implicitWidth: layout.implicitWidth + 20

    ColumnLayout {
        id: layout
        anchors.fill: parent
        anchors.margins: 10
        Button {
            text: "New..."
            onClicked: root.myData.reset();
        }
        Button {
            text: "Open..."
            onClicked: {
                fileDialog.fileMode = FileDialog.OpenFile
                if (root.myData) {
                    if (root.myData.path)
                        fileDialog.currentFolder = root.myData.path
                }
                fileDialog.open()
            }
        }
        Button {
            text: "Save..."
            onClicked: {
                fileDialog.fileMode = FileDialog.SaveFile
                if (root.myData) {
                    if (root.myData.path)
                        fileDialog.currentFolder = root.myData.path
                }
                fileDialog.open()
            }
        }
    }

    FileDialog {
        id: fileDialog
        nameFilters: ["JSON Files (*.json)"]
        onAccepted: {
            switch(fileMode) {
            case FileDialog.SaveFile:
                root.myData.save(selectedFile);
                break;
            case FileDialog.OpenFile:
                root.myData.load(selectedFile);
                break;
            default:
                //Nothing to do
            }
        }

    }
}
