import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    property MyObject myData: null

    id: root
    title: qsTr("Objects")

    MySelectionWrapper {
        id: mng
        model: MyModels.objectModel
        onCurrentDataChanged: root.myData = currentData
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
            "type": MyModel.Type.Object,
        }
    }

    partA: FSEPlacement {
        placement: root.myData
    }
}
