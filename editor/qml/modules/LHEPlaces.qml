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
        onCreateClicked: { MyProject.createPlace() }
        onRemoveClicked: { if (mng.currentData) MyProject.removePlace(mng.currentData) }
        onDuplicateClicked: { if (mng.currentData) MyProject.duplicatePlace(mng.currentData) }
    }

    placement: LHEEntity {
        entity: root.myData
    }
}
