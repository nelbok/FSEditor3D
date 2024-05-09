import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Dialogs

import LHEditor

LHEModule {
    id: root
    title: qsTr("Project")

    selection: ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        spacing: 5

        LHEMenuButton {
            text: qsTr("New")
            onClicked: MyProject.reset();
        }

        LHEMenuButton {
            text: qsTr("Load")
            onClicked: openDialog(FileDialog.OpenFile);
        }

        LHEMenuButton {
            text: qsTr("Save")
            onClicked: openDialog(FileDialog.SaveFile);
        }
    }

    placement: LHEEntity {
        entity: MyProject
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
