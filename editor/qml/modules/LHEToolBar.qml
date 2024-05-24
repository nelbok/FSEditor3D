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
            onClicked: MyManager.reset()
        }

        LHEToolButton {
            source: "qrc:/tools/load.svg"
            onClicked: openDialog(FileDialog.OpenFile)
        }

        LHEToolButton {
            source: "qrc:/tools/save.svg"
            onClicked: openDialog(FileDialog.SaveFile)
        }

        LHEToolButton {
            source: "qrc:/tools/undo.svg"
            enabled: MyCommands.canUndo
            onClicked: MyCommands.undo()
        }

        LHEToolButton {
            source: "qrc:/tools/redo.svg"
            enabled: MyCommands.canRedo
            onClicked: MyCommands.redo()
        }
    }

    function openDialog(fileMode) {
        dialog.fileMode = fileMode
        if (!MyProject.isTemp && MyProject.path)
            dialog.currentFolder = MyProject.path
        dialog.open()
    }

    FileDialog {
        id: dialog
        nameFilters: ["JSON Files (*.json)"]
        onAccepted: {
            switch(fileMode) {
            case FileDialog.SaveFile:
                MyManager.save(selectedFile)
                break;
            case FileDialog.OpenFile:
                MyManager.load(selectedFile)
                break;
            default:
                //Nothing to do
            }
        }
    }

    Shortcut {
        sequences: [ StandardKey.Save ]
        onActivated: { openDialog(FileDialog.SaveFile) }
    }

    Shortcut {
        sequences: [ StandardKey.Open ]
        onActivated: { openDialog(FileDialog.OpenFile) }
    }

    Shortcut {
        sequences: [ StandardKey.Undo ]
        onActivated: { if (MyCommands.canUndo) MyCommands.undo() }
    }

    Shortcut {
        sequences: [ StandardKey.Redo ]
        onActivated: { if (MyCommands.canRedo) MyCommands.redo() }
    }
}
