import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs

import editor

FSEModule {
    title: qsTr("Models")

    selection: FSEList {
        model: MyModels.modelModel

        onCreateClicked: { MyCommands.projectCommand.createModel() }
        onRemoveClicked: { MyCommands.projectCommand.removeModel(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateModel(mng.currentData) }
        onCurrentDataChanged: (currentData) => { MySelection.currentModel = currentData }
    }

    entity: FSEEntity {
        entity: MySelection.currentModel
    }

    partA: ColumnLayout {
        spacing: 5
        enabled: MySelection.currentModel

        FSEComboBox {
            name: qsTr("Type")
            model: ListModel {
                ListElement { uuid: MyModel.ModelType.Object; name: qsTr("Object") }
                ListElement { uuid: MyModel.ModelType.Link; name: qsTr("Link") }
                ListElement { uuid: MyModel.ModelType.Place; name: qsTr("Place") }
            }
            currentIndex: (MySelection.currentModel) ? indexOfValue(MySelection.currentModel.modelType) : -1
            onActivated: {
                if (MySelection.currentModel)
                    MyCommands.modelCommand.setModelType(MySelection.currentModel, valueAt(currentIndex))
            }
        }

        RowLayout {
            height: 40

            spacing: 5

            FSEText {
                text: qsTr("Source")

                Layout.preferredWidth: 80
            }

            FSEMenuButton {
                text: (MySelection.currentModel && MySelection.currentModel.sourcePath.toString() !== "") ? MySelection.currentModel.sourcePath : qsTr("Choose...")
                onClicked: dialog.open()
            }
        }

        FSETextField {
            name: qsTr("QML name")
            value: (MySelection.currentModel) ? MySelection.currentModel.qmlName : "-"
            enabled: false
        }
    }

    Connections {
        target: MyManager.balsam
        function onErrorOccurred() { message.open() }
    }

    FileDialog {
        id: dialog
        fileMode: FileDialog.OpenFile
        nameFilters: [
            "Wavefront (*.obj)",
            "COLLADA (*.dae)",
            "FBX (*.fbx)",
            "STL (*.stl)",
            "PLY (*.ply)",
            "GLTF2 (*.gltf *.glb)",
        ]
        onAccepted: MyManager.balsam.generate(myData, selectedFile)
    }

    MessageDialog {
        id: message
        buttons: MessageDialog.Ok
        text: qsTr("An error occurred while parsing the file.")
    }
}
