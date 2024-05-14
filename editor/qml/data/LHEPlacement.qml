import QtQuick

import editor

LHEEntity {
    property MyPlacement placement: null

    id: root

    entity: placement

    LHEVector3DField {
        name: qsTr("Position")
        value: (root.placement) ? root.placement.position : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.placement) root.placement.position = value }
    }

    LHEVector3DField {
        name: qsTr("Rotation")
        value: (root.placement) ? root.placement.rotation : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.placement) root.placement.rotation = value }
    }

    LHEComboBox {
        name: qsTr("Place")

        MyEntityModel {
            id: myModel
            model: (MyProject) ? MyProject.places : null
            currentData: (root.placement) ? root.placement.place : null
            onCurrentDataUpdated: { if (root.placement && root.placement.place !== currentData) root.placement.place = currentData }
        }

        model: myModel
        currentIndex: myModel.currentIndex
        onActivated: myModel.currentIndex = currentIndex
    }
}
