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
        onItemClicked: (index) => { mng.currentIndex = index }
        onCreateClicked: { MyProject.createLink() }
        onRemoveClicked: { if (mng.currentData) MyProject.removeLink(mng.currentData) }
        onDuplicateClicked: { if (mng.currentData) MyProject.duplicateLink(mng.currentData) }
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
                onCurrentUpdated: { if (root.myData && root.myData.link !== currentData) root.myData.link = currentData }
            }

            model: subMng.model
            currentIndex: subMng.currentIndex
            onActivated: subMng.currentIndex = currentIndex
        }
    }
}
