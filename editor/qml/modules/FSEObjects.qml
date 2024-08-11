import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    property MyObject myData: MySelection.currentObject

    // FIXME: FSEModule doesn't work if we don't have id: root here...
    id: root
    title: qsTr("Objects")

    MySelectionWrapper {
        id: mng
        model: MyModels.objectModel
        onCurrentDataChanged: MySelection.currentObject = currentData
    }

    selection: FSEList {
        model: mng.model
        currentIndex: mng.currentIndex
        removeEnabled: mng.currentData && !mng.currentData.hasRef
        duplicateEnabled: mng.currentData

        onCreateClicked: { MyCommands.projectCommand.createObject() }
        onRemoveClicked: { MyCommands.projectCommand.removeObject(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateObject(mng.currentData) }
        onItemClicked: (index) => { mng.currentIndex = index }
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
