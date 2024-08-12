import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    title: qsTr("Links")

    selection: FSEList {
        model: MyModels.linkModel

        onCreateClicked: { MyCommands.projectCommand.createLink() }
        onRemoveClicked: { MyCommands.projectCommand.removeLink(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateLink(mng.currentData) }
        onCurrentDataChanged: (currentData) => { MySelection.currentLink = currentData }
    }

    entity: FSEShape {
        shape: MySelection.currentLink
        filters: {
            "modelType": MyModel.ModelType.Link,
        }
    }

    partA: FSEPlacement {
        placement: MySelection.currentLink
    }

    partB: ColumnLayout {
        spacing: 5
        enabled: MySelection.currentLink
        FSEComboBox {
            name: qsTr("Link")

            MySelectionWrapper {
                id: mng
                model: MyModels.linkModel
                project: MyProject
                currentData: (MySelection.currentLink) ? MySelection.currentLink.link : null
                onCurrentUpdated: {
                    if (MySelection.currentLink && MySelection.currentLink.link !== currentData)
                        MyCommands.linkCommand.setLink(MySelection.currentLink, currentData)
                }
            }

            model: mng.model
            currentIndex: mng.currentIndex
            onActivated: mng.currentIndex = currentIndex
        }
    }
}
