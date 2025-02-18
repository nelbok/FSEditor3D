import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    selection: FSEList {
        model: MyModels.entryPointModel
        currentData: MySelection.currentEntryPoint
        onActivated: MySelection.currentEntryPoint = currentData

        onCreateClicked: { MySelection.currentEntryPoint = MyCommands.projectCommand.createEntryPoint() }
        onRemoveClicked: { MyCommands.projectCommand.removeEntryPoint(MySelection.currentEntryPoint) }
        onDuplicateClicked: { MySelection.currentEntryPoint = MyCommands.projectCommand.duplicateEntryPoint(MySelection.currentEntryPoint) }
    }

    entity: FSEEntity {
        entity: MySelection.currentEntryPoint
    }

    partA: ColumnLayout {
        spacing: 5
        enabled: MySelection.currentEntryPoint

        FSEVector3DField {
            name: qsTr("Position")
            value: (MySelection.currentEntryPoint) ? MySelection.currentEntryPoint.position : Qt.vector3d(0, 0, 0)
            onEditingFinished: (value) => {
                if (MySelection.currentEntryPoint)
                    MyCommands.entryPointCommand.setPosition(MySelection.currentEntryPoint, value)
            }
        }

        FSEVector3DField {
            name: qsTr("Rotation")
            xEnabled: false
            zEnabled: false
            value: Qt.vector3d(0, (MySelection.currentEntryPoint) ? MySelection.currentEntryPoint.rotation : 0, 0)
            onEditingFinished: (value) => {
                if (MySelection.currentEntryPoint)
                    MyCommands.entryPointCommand.setRotation(MySelection.currentEntryPoint, value.y)
            }
        }

        FSEComboBox {
            name: qsTr("Place")

            MySelectionWrapper {
                id: mng
                model: MyModels.placeModelWithNone
                currentData: (MySelection.currentEntryPoint) ? MySelection.currentEntryPoint.place : null
                onCurrentUpdated: {
                    if (MySelection.currentEntryPoint && MySelection.currentEntryPoint.place !== currentData)
                        MyCommands.entryPointCommand.setPlace(MySelection.currentEntryPoint, currentData)
                }
            }

            model: mng.model
            currentIndex: mng.currentIndex
            onActivated: mng.currentIndex = currentIndex
        }
    }

    partB: ColumnLayout {
        spacing: 5
        enabled: MySelection.currentEntryPoint

        RowLayout {
            implicitHeight: 40

            spacing: 5

            Item {
                Layout.preferredWidth: 80
            }

            FSEMenuButton {
                text: qsTr("Assign camera coord.")
                onClicked: MyCommands.entryPointCommand.assignCameraCoordinates(MySelection.currentEntryPoint, MyPreview)
            }
        }
    }
}
