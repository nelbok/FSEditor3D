import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    property MyLink myData: null

    id: root
    title: qsTr("Links")

    MySelectionWrapper {
        id: mng
        model: MyModels.linkModel
        onCurrentDataChanged: root.myData = currentData
    }

    selection: FSEList {
        model: mng.model
        currentIndex: mng.currentIndex
        removeEnabled: mng.currentData && !mng.currentData.hasRef
        duplicateEnabled: mng.currentData

        onCreateClicked: { MyCommands.projectCommand.createLink() }
        onRemoveClicked: { MyCommands.projectCommand.removeLink(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateLink(mng.currentData) }
        onItemClicked: (index) => { mng.currentIndex = index }
    }

    placement: FSEPlacement {
        placement: root.myData
        filters: {
            "type": MyModel.Type.Link,
        }
    }

    partA: ColumnLayout {
        spacing: 5
        enabled: root.myData
        FSEComboBox {
            name: qsTr("Link")

            MySelectionWrapper {
                id: subMng
                model: MyModels.linkModel
                currentData: (root.myData) ? root.myData.link : null
                onCurrentUpdated: { if (root.myData && root.myData.link !== currentData) MyCommands.linkCommand.setLink(root.myData, currentData) }
            }

            model: subMng.model
            currentIndex: subMng.currentIndex
            onActivated: subMng.currentIndex = currentIndex
        }
    }
}
