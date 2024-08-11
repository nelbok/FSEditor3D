import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    property MyPlace myData: MySelection.currentPlace

    // FIXME: FSEModule doesn't work if we don't have id: root here...
    id: root
    title: qsTr("Places")

    selection: FSEList {
        model: MyModels.placeModel

        onCreateClicked: { MyCommands.projectCommand.createPlace() }
        onRemoveClicked: { MyCommands.projectCommand.removePlace(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicatePlace(mng.currentData) }
        onCurrentDataChanged: (currentData) => { MySelection.currentPlace = currentData }
    }

    entity: FSEShape {
        shape: root.myData
        filters: {
            "modelType": MyModel.ModelType.Place,
        }
    }
}
