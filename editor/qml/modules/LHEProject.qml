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

    partA: ComboBox {
        textRole: "name"
        model: (MyProject) ? MyProject.places : null
        currentIndex: {
            if (MyProject)
                for(var i in MyProject.places)
                    if (MyProject.places[i].uuid === MyProject.defaultPlace.uuid)
                        return i;
            return -1
        }
        onCurrentIndexChanged: {
            var value = valueAt(currentIndex)
            if (MyProject && value)
                MyProject.defaultPlace = value
        }
    }


    function openDialog(fileMode) {
        fileDialog.fileMode = fileMode
        if (MyProject) {
            if (MyProject.path)
                fileDialog.currentFolder = MyProject.path
        }
        fileDialog.open()
    }

    FileDialog {
        id: fileDialog
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
