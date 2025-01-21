import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs

import editor

FSEModule {
    title: qsTr("Models")

    selection: FSEList {
        model: MyModels.modelModel
        currentData: MySelection.currentModel
        onActivated: MySelection.currentModel = currentData

        onCreateClicked: { MyCommands.projectCommand.createModel() }
        onRemoveClicked: { MyCommands.projectCommand.removeModel(MySelection.currentModel) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateModel(MySelection.currentModel) }
    }

    entity: FSEEntity {
        entity: MySelection.currentModel
    }

    partA: FSEGeometry {
        geometry: MySelection.currentModel
    }

    partB: ColumnLayout {
        spacing: 5
        enabled: MySelection.currentModel

        FSEComboBox {
            name: qsTr("Type")
            enabled: (MySelection.currentModel) ? !MySelection.currentModel.hasRef : false
            model: ListModel {
                ListElement { value: MyModel.ModelType.Object; name: qsTr("Object") }
                ListElement { value: MyModel.ModelType.Link; name: qsTr("Link") }
                ListElement { value: MyModel.ModelType.Place; name: qsTr("Place") }
            }
            currentIndex: (MySelection.currentModel) ? indexOfValue(MySelection.currentModel.modelType) : -1
            onActivated: {
                if (MySelection.currentModel)
                    MyCommands.modelCommand.setModelType(MySelection.currentModel, valueAt(currentIndex))
            }
        }

        RowLayout {
            implicitHeight: 40

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
        onAccepted: MyManager.balsam.generate(MySelection.currentModel, selectedFile)
    }
}
