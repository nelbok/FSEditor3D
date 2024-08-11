import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs

import editor

FSEModule {
    property MyModel myData: MySelection.currentModel

    // FIXME: FSEModule doesn't work if we don't have id: root here...
    id: root
    title: qsTr("Models")

    MySelectionWrapper {
        id: mng
        model: MyModels.modelModel
        onCurrentDataChanged: MySelection.currentModel = currentData
    }

    selection: FSEList {
        model: mng.model
        currentIndex: mng.currentIndex
        removeEnabled: mng.currentData && !mng.currentData.hasRef
        duplicateEnabled: mng.currentData

        onCreateClicked: { MyCommands.projectCommand.createModel() }
        onRemoveClicked: { MyCommands.projectCommand.removeModel(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateModel(mng.currentData) }
        onItemClicked: (index) => { mng.currentIndex = index }
    }

    entity: FSEEntity {
        entity: root.myData
    }

    partA: ColumnLayout {
        spacing: 5
        enabled: root.myData

        FSEComboBox {
            name: qsTr("Type")
            model: ListModel {
                ListElement { uuid: MyModel.ModelType.Object; name: qsTr("Object") }
                ListElement { uuid: MyModel.ModelType.Link; name: qsTr("Link") }
                ListElement { uuid: MyModel.ModelType.Place; name: qsTr("Place") }
            }
            currentIndex: (root.myData) ? indexOfValue(root.myData.modelType) : -1
            onActivated: { if (root.myData) MyCommands.modelCommand.setModelType(root.myData, valueAt(currentIndex)) }
        }

        RowLayout {
            height: 40

            spacing: 5

            FSEText {
                text: qsTr("Source")

                Layout.preferredWidth: 80
            }

            FSEMenuButton {
                text: (root.myData && root.myData.sourcePath.toString() !== "") ? root.myData.sourcePath : qsTr("Choose...")
                onClicked: dialog.open()
            }
        }

        FSETextField {
            name: qsTr("QML name")
            value: (root.myData) ? root.myData.qmlName : "-"
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
