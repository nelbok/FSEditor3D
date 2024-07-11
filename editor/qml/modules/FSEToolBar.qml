import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs

import editor

FSERectangle {
    signal settingsClicked

    id: root
    width: 50
    height: 275

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.current.newFile + ".svg"
            onClicked: MyManager.reset()
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.current.loadFile + ".svg"
            onClicked: openDialog(FileDialog.OpenFile)
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.current.saveFile + ".svg"
            onClicked: openDialog(FileDialog.SaveFile)
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.current.undo + ".svg"
            enabled: MyCommands.canUndo
            onClicked: MyCommands.undo()
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.current.redo + ".svg"
            enabled: MyCommands.canRedo
            onClicked: MyCommands.redo()
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.current.settings + ".svg"
            onClicked: root.settingsClicked()
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
