import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    title: qsTr("Objects")

    selection: FSEList {
        model: MyModels.objectModel

        onCreateClicked: { MyCommands.projectCommand.createObject() }
        onRemoveClicked: { MyCommands.projectCommand.removeObject(MySelection.currentObject) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateObject(MySelection.currentObject) }
        onCurrentDataChanged: (currentData) => { MySelection.currentObject = currentData }
    }

    entity: FSEShape {
        shape: MySelection.currentObject
        filters: {
            "modelType": MyModel.ModelType.Object,
        }
    }

    partA: FSEPlacement {
        placement: MySelection.currentObject
    }
}
