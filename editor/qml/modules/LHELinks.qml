import QtQuick
import QtQuick.Layouts

import editor

LHEModule {
    property MyLink myData: null

    id: root
    title: qsTr("Links")

    MySelectionManager {
        id: mng
        model: MyController.linkModel
        onCurrentDataChanged: root.myData = currentData
    }

    selection: LHEList {
        model: mng.model
        currentIndex: mng.currentIndex
        removeEnabled: mng.currentData && !mng.currentData.hasRef
        duplicateEnabled: mng.currentData

        onCreateClicked: { MyController.projectCommand.createLink() }
        onRemoveClicked: { MyController.projectCommand.removeLink(mng.currentData) }
        onDuplicateClicked: { MyController.projectCommand.duplicateLink(mng.currentData) }
        onItemClicked: (index) => { mng.currentIndex = index }
    }

    placement: LHEPlacement {
        placement: root.myData
    }

    partA: ColumnLayout {
        spacing: 5
        enabled: root.myData
        LHEComboBox {
            name: qsTr("Link")

            MySelectionManager {
                id: subMng
                model: MyController.linkModel
                currentData: (root.myData) ? root.myData.link : null
                onCurrentUpdated: { if (root.myData && root.myData.link !== currentData) MyController.linkCommand.setLink(root.myData, currentData) }
            }

            model: subMng.model
            currentIndex: subMng.currentIndex
            onActivated: subMng.currentIndex = currentIndex
        }
    }
}
