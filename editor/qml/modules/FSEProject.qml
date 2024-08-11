import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    id: root
    title: qsTr("Project")

    entity: FSEEntity {
        entity: MyProject
    }

    partA: ColumnLayout{
        spacing: 5
        FSEComboBox {
            name: qsTr("Default place")

            MySelectionWrapper {
                id: mng
                model: MyModels.placeModel
                project: MyProject
                currentData: MyProject.defaultPlace
                onCurrentUpdated: { if (MyProject && MyProject.defaultPlace !== currentData) MyCommands.projectCommand.setDefaultPlace(currentData) }
            }

            model: mng.model
            currentIndex: mng.currentIndex
            onActivated: mng.currentIndex = currentIndex
        }
    }
}
