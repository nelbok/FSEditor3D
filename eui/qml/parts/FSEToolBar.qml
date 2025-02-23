import QtQuick
import QtQuick.Layouts

import eui

FSERectangle {
    width: 50
    height: 275

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.style.icons.newFile + ".svg"
            onClicked: MyInterface.reset()
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.style.icons.loadFile + ".svg"
            onClicked: MyInterface.load()
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.style.icons.saveFile + ".svg"
            onClicked: MyInterface.save()

            FSERectangle {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.margins: -2.5
                width: 10
                height:10
                visible: MyCommands.isModified
            }
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.style.icons.undo + ".svg"
            enabled: MyCommands.canUndo
            onClicked: MyCommands.undo()
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.style.icons.redo + ".svg"
            enabled: MyCommands.canRedo
            onClicked: MyCommands.redo()
        }

        FSEToolButton {
            source: "qrc:/tools/" + MyStyles.style.icons.settings + ".svg"
            onClicked: {
                MySelection.currentType = (MySelection.currentType === MySelection.Type.Settings) ? MySelection.Type.None : MySelection.Type.Settings
            }
        }
    }

    Shortcut {
        sequences: [ StandardKey.Save ]
        onActivated: { MyInterface.save() }
    }

    Shortcut {
        sequences: [ StandardKey.Open ]
        onActivated: { MyInterface.load() }
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
