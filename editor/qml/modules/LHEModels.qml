import QtQuick
import QtQuick.Layouts

import editor

LHEModule {
    property MyModel myData: null

    id: root
    title: qsTr("Models")

    MySelectionManager {
        id: mng
        model: MyController.modelModel
        onCurrentDataChanged: root.myData = currentData
    }

    selection: LHEList {
        model: mng.model
        currentIndex: mng.currentIndex
        removeEnabled: mng.currentData && !mng.currentData.hasRef
        duplicateEnabled: mng.currentData

        onCreateClicked: { MyController.projectCommand.createModel() }
        onRemoveClicked: { MyController.projectCommand.removeModel(mng.currentData) }
        onDuplicateClicked: { MyController.projectCommand.duplicateModel(mng.currentData) }
        onItemClicked: (index) => { mng.currentIndex = index }
    }

    placement: LHEEntity {
        entity: root.myData
    }
}
