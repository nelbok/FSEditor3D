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
        onItemClicked: (index) => { mng.currentIndex = index }
        onCreateClicked: { MyController.projectCommand.createPlace() }
        onRemoveClicked: { if (mng.currentData) MyController.projectCommand.removePlace(mng.currentData) }
        onDuplicateClicked: { if (mng.currentData) MyController.projectCommand.duplicatePlace(mng.currentData) }
    }

    placement: LHEEntity {
        entity: root.myData
    }
}
