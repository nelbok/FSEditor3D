import QtQuick
import QtQuick.Layouts

import editor

LHEModule {
    id: root
    title: qsTr("Project")

    placement: LHEEntity {
        entity: MyProject
    }

    partA: ColumnLayout{
        spacing: 5
        LHEComboBox {
            name: qsTr("Default place")

            MySelectionWrapper {
                id: mng
                model: MyModels.placeModel
                currentData: MyProject.defaultPlace
                onCurrentUpdated: { if (MyProject && MyProject.defaultPlace !== currentData) MyCommands.projectCommand.setDefaultPlace(currentData) }
            }

            model: mng.model
            currentIndex: mng.currentIndex
            onActivated: mng.currentIndex = currentIndex
        }
    }
}
