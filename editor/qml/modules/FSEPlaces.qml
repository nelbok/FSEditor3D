import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    property MyPlace myData: MySelection.currentPlace

    // FIXME: FSEModule doesn't work if we don't have id: root here...
    id: root
    title: qsTr("Places")

    MySelectionWrapper {
        id: mng
        model: MyModels.placeModel
        project: MyProject
        onCurrentDataChanged: MySelection.currentPlace = currentData
    }

    selection: FSEList {
        model: mng.model
        currentIndex: mng.currentIndex
        removeEnabled: mng.currentData && !mng.currentData.hasRef
        duplicateEnabled: mng.currentData

        onCreateClicked: { MyCommands.projectCommand.createPlace() }
        onRemoveClicked: { MyCommands.projectCommand.removePlace(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicatePlace(mng.currentData) }
        onItemClicked: (index) => { mng.currentIndex = index }
    }

    entity: FSEShape {
        shape: root.myData
        filters: {
            "modelType": MyModel.ModelType.Place,
        }
    }
}
