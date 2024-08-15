import QtQuick
import QtQuick.Layouts

import editor

FSEGeometry {
    property MyPlacement placement: null

    id: root

    geometry: placement

    FSEComboBox {
        name: qsTr("Place")

        MySelectionWrapper {
            id: mng
            model: MyModels.placeModelWithNone
            currentData: (root.placement) ? root.placement.place : null
            onCurrentUpdated: { if (root.placement && root.placement.place !== currentData) MyCommands.placementCommand.setPlace(root.placement, currentData) }
        }

        model: mng.model
        currentIndex: mng.currentIndex
        onActivated: mng.currentIndex = currentIndex
    }
}
