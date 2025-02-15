import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    selection: FSEList {
        model: MyModels.objectModel
        currentData: MySelection.currentObject
        onActivated: MySelection.currentObject = currentData

        onCreateClicked: { MySelection.currentObject = MyCommands.projectCommand.createObject() }
        onRemoveClicked: { MyCommands.projectCommand.removeObject(MySelection.currentObject) }
        onDuplicateClicked: { MySelection.currentObject = MyCommands.projectCommand.duplicateObject(MySelection.currentObject) }
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
