import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    property MyLink myData: MySelection.currentLink

    // FIXME: FSEModule doesn't work if we don't have id: root here...
    id: root
    title: qsTr("Links")

    selection: FSEList {
        model: MyModels.linkModel

        onCreateClicked: { MyCommands.projectCommand.createLink() }
        onRemoveClicked: { MyCommands.projectCommand.removeLink(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateLink(mng.currentData) }
        onCurrentDataChanged: (currentData) => { MySelection.currentLink = currentData }
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
                project: MyProject
                currentData: (root.myData) ? root.myData.link : null
                onCurrentUpdated: { if (root.myData && root.myData.link !== currentData) MyCommands.linkCommand.setLink(root.myData, currentData) }
            }

            model: subMng.model
            currentIndex: subMng.currentIndex
            onActivated: subMng.currentIndex = currentIndex
        }
    }
}
