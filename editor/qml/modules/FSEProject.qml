import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    title: qsTr("Project")

    entity: FSEEntity {
        entity: MyProject
    }

    partA: FSEGeometry {
        geometry: MyProject
    }

    partB: ColumnLayout{
        spacing: 5
        FSEComboBox {
            name: qsTr("Default place")

            MySelectionWrapper {
                id: mng
                model: MyModels.placeModel
                currentData: MyProject.defaultPlace
                onCurrentUpdated: {
                    if (MyProject && MyProject.defaultPlace !== currentData)
                        MyCommands.projectCommand.setDefaultPlace(currentData)
                }
            }

            model: mng.model
            currentIndex: mng.currentIndex
            onActivated: mng.currentIndex = currentIndex
        }
    }
}
