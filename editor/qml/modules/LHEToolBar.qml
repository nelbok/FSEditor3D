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
            onClicked: MyController.reset();
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
            onClicked: { if (MyController.commands.canUndo) MyController.commands.undo() }
        }

        LHEToolButton {
            source: "qrc:/tools/redo.svg"
            onClicked: { if (MyController.commands.canRedo) MyController.commands.redo() }
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
                MyController.save(selectedFile);
                break;
            case FileDialog.OpenFile:
                MyController.load(selectedFile);
                break;
            default:
                //Nothing to do
            }
        }
    }
}
