import QtQuick

import LHEditor

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
        name: "Places"
        model: (MyProject) ? MyProject.places : null
        currentIndex: (root.placement && root.placement.place) ? indexOfValue(root.placement.place.uuid) : -1
        onActivated: { if (root.placement) root.placement.place = model[currentIndex] }
    }
}
