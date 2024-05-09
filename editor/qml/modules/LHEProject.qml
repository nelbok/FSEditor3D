import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Dialogs

import LHEditor

LHEModule {
    id: root
    title: qsTr("Project")

    selection: ColumnLayout {
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

    partA: ColumnLayout{
        spacing: 5
        LHEComboBox {
            name: qsTr("Default place")
            model: (MyProject) ? MyProject.places : null
            currentIndex: {
                if (MyProject.defaultPlace)
                    for(var i in MyProject.places) {
                        if (MyProject.places[i].uuid === MyProject.defaultPlace.uuid)
                            return i
                    }
                return -1
            }
            onActivated: { if (MyProject) MyProject.defaultPlace = MyProject.places[currentIndex] }
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
