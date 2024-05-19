import QtQuick
import QtQuick.Layouts

import editor

LHEModule {
    property MyPlace myData: null

    id: root
    title: qsTr("Places")

    MySelectionManager {
        id: mng
        model: MyController.placeModel
        onCurrentDataChanged: root.myData = currentData
    }

    selection: LHEList {
        model: mng.model
        currentIndex: mng.currentIndex
        removeEnabled: mng.currentData && !mng.currentData.hasRef
        duplicateEnabled: mng.currentData

        onCreateClicked: { MyController.projectCommand.createPlace() }
        onRemoveClicked: { MyController.projectCommand.removePlace(mng.currentData) }
        onDuplicateClicked: { MyController.projectCommand.duplicatePlace(mng.currentData) }
        onItemClicked: (index) => { mng.currentIndex = index }
    }

    placement: LHEEntity {
        entity: root.myData
    }
}
