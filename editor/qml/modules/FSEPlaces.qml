import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    title: qsTr("Places")

    selection: FSEList {
        model: MyModels.placeModel

        onCreateClicked: { MyCommands.projectCommand.createPlace() }
        onRemoveClicked: { MyCommands.projectCommand.removePlace(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicatePlace(mng.currentData) }
        onCurrentDataChanged: (currentData) => { MySelection.currentPlace = currentData }
    }

    entity: FSEShape {
        shape: MySelection.currentPlace
        filters: {
            "modelType": MyModel.ModelType.Place,
        }
    }
}
