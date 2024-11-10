import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    title: qsTr("Places")

    selection: FSEList {
        model: MyModels.placeModel
        currentData: MySelection.currentPlace
        onActivated: MySelection.currentPlace = currentData

        onCreateClicked: { MyCommands.projectCommand.createPlace() }
        onRemoveClicked: { MyCommands.projectCommand.removePlace(MySelection.currentPlace) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicatePlace(MySelection.currentPlace) }
    }

    entity: FSEShape {
        shape: MySelection.currentPlace
        filters: {
            "modelType": MyModel.ModelType.Place,
        }
    }

    partA: FSEGeometry {
        geometry: MySelection.currentPlace
    }
}
