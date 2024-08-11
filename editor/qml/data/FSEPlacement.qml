import QtQuick
import QtQuick.Layouts

import editor

ColumnLayout {
    property MyPlacement placement: null

    id: root

    spacing: 5
    enabled: root.placement

    FSEVector3DField {
        name: qsTr("Position")
        value: (root.placement) ? root.placement.position : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.placement) MyCommands.placementCommand.setPosition(root.placement, value) }
    }

    FSEVector3DField {
        name: qsTr("Rotation")
        value: (root.placement) ? root.placement.rotation : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.placement) MyCommands.placementCommand.setRotation(root.placement, value) }
    }

    FSEComboBox {
        name: qsTr("Place")

        MySelectionWrapper {
            id: mng
            model: MyModels.placeModel
            project: MyProject
            currentData: (root.placement) ? root.placement.place : null
            onCurrentUpdated: { if (root.placement && root.placement.place !== currentData) MyCommands.placementCommand.setPlace(root.placement, currentData) }
        }

        model: mng.model
        currentIndex: mng.currentIndex
        onActivated: mng.currentIndex = currentIndex
    }
}
