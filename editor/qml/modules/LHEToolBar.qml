import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs

import editor

LHERectangle {
    id: root
    width: 50
    height: 230

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        LHEToolButton {
            source: "qrc:/tools/new.svg"
            onClicked: MyProject.reset();
        }

        LHEToolButton {
            source: "qrc:/tools/load.svg"
            onClicked: openDialog(FileDialog.OpenFile);
        }

        LHEToolButton {
            source: "qrc:/tools/save.svg"
            onClicked: openDialog(FileDialog.SaveFile);
        }

        LHEToolButton {
            source: "qrc:/tools/undo.svg"
            onClicked: console.log("Undo not implemented yet")
        }

        LHEToolButton {
            source: "qrc:/tools/redo.svg"
            onClicked: console.log("Redo not implemented yet")
        }
    }

    function openDialog(fileMode) {
        dialog.fileMode = fileMode
        if (MyProject) {
            if (MyProject.path)
                dialog.currentFolder = MyProject.path
        }
        dialog.open()
    }

    FileDialog {
        id: dialog
        nameFilters: ["JSON Files (*.json)"]
        onAccepted: {
            switch(fileMode) {
            case FileDialog.SaveFile:
                MyProject.save(selectedFile);
                break;
            case FileDialog.OpenFile:
                MyProject.load(selectedFile);
                break;
            default:
                //Nothing to do
            }
        }
    }
}
