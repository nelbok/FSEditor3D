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

        Item {
            height: 40
        }

        FSEComboBox {
            MySelectionWrapper {
                id: wrapEP
                model: MyModels.entryPointModel
            }
            model: wrapEP.model
            currentIndex: wrapEP.currentIndex
            onActivated: wrapEP.currentIndex = currentIndex
        }

        RowLayout {
            implicitHeight: 40

            spacing: 5

            Item {
                Layout.preferredWidth: 80
            }

            FSEMenuButton {
                text: qsTr("Teleport")
                enabled: wrapEP.currentIndex !== -1
                onClicked: MyPreview.teleportOn(wrapEP.currentData)
            }
        }
    }
}
