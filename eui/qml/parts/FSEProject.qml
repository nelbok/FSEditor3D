import QtQuick
import QtQuick.Layouts

import eui

FSEModule {
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
                model: MyModels.placeModelWithNone
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

        // FSESpinBox {
        //     name: qsTr("Person height")
        //     from: 110
        //     to: 300
        //     value: MyProject.height
        //     onValueModified: () => { MyProject.height = value }
        // }
    }
}
