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
        model: (MyProject) ? MyProject.places : null
        currentIndex: {
            if (root.placement && root.placement.place)
                for(var i in MyProject.places) {
                    if (MyProject.places[i].uuid === root.placement.place.uuid)
                        return i
                }
            return -1
        }
        onActivated: { if (root.placement) root.placement.place = model[currentIndex] }
    }
}
