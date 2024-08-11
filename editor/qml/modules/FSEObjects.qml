import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    property MyObject myData: MySelection.currentObject

    // FIXME: FSEModule doesn't work if we don't have id: root here...
    id: root
    title: qsTr("Objects")

    selection: FSEList {
        model: MyModels.objectModel

        onCreateClicked: { MyCommands.projectCommand.createObject() }
        onRemoveClicked: { MyCommands.projectCommand.removeObject(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateObject(mng.currentData) }
        onCurrentDataChanged: (currentData) => { MySelection.currentObject = currentData }
    }

    entity: FSEShape {
        shape: root.myData
        filters: {
            "modelType": MyModel.ModelType.Object,
        }
    }

    partA: FSEPlacement {
        placement: root.myData
    }
}
