import QtQuick
import QtQuick.Layouts

import eui

FSEModule {
    selection: FSEList {
        model: MyModels.linkModel
        currentData: MySelection.currentLink
        onActivated: MySelection.currentLink = currentData

        onCreateClicked: { MySelection.currentLink = MyCommands.projectCommand.createLink() }
        onRemoveClicked: { MyCommands.projectCommand.removeLink(MySelection.currentLink) }
        onDuplicateClicked: { MySelection.currentLink = MyCommands.projectCommand.duplicateLink(MySelection.currentLink) }
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
                model: MyModels.linkModelWithNone
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
