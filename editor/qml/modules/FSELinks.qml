import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    property MyLink myData: MySelection.currentLink

    // FIXME: FSEModule doesn't work if we don't have id: root here...
    id: root
    title: qsTr("Links")

    MySelectionWrapper {
        id: mng
        model: MyModels.linkModel
        onCurrentDataChanged: MySelection.currentLink = currentData
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

    entity: FSEShape {
        shape: root.myData
        filters: {
            "modelType": MyModel.ModelType.Link,
        }
    }

    partA: FSEPlacement {
        placement: root.myData
    }

    partB: ColumnLayout {
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
