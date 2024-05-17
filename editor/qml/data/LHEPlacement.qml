import QtQuick

import editor

LHEEntity {
    property MyPlacement placement: null

    id: root

    entity: placement

    LHEVector3DField {
        name: qsTr("Position")
        value: (root.placement) ? root.placement.position : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.placement) MyController.placementCommand.setPosition(root.placement, value) }
    }

    LHEVector3DField {
        name: qsTr("Rotation")
        value: (root.placement) ? root.placement.rotation : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.placement) MyController.placementCommand.setRotation(root.placement, value) }
    }

    LHEComboBox {
        name: qsTr("Place")

        MySelectionManager {
            id: mng
            model: MyController.placeModel
            currentData: (root.placement) ? root.placement.place : null
            onCurrentUpdated: { if (root.placement && root.placement.place !== currentData) MyController.placementCommand.setPlace(root.placement, currentData) }
        }

        model: mng.model
        currentIndex: mng.currentIndex
        onActivated: mng.currentIndex = currentIndex
    }
}
