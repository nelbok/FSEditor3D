import QtQuick
import QtQuick.Layouts

import eui

ColumnLayout {
    property MyGeometry geometry: null

    id: root

    spacing: 5
    enabled: root.geometry

    FSEVector3DField {
        name: qsTr("Position")
        value: (root.geometry) ? root.geometry.localPosition : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.geometry) MyCommands.geometryCommand.setLocalPosition(root.geometry, value) }
    }

    FSEVector3DField {
        name: qsTr("Rotation")
        value: (root.geometry) ? root.geometry.localRotation : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.geometry) MyCommands.geometryCommand.setLocalRotation(root.geometry, value) }
    }

    FSEVector3DField {
        name: qsTr("Scale")
        value: (root.geometry) ? root.geometry.localScale : Qt.vector3d(1, 1, 1)
        onEditingFinished: (value) => { if (root.geometry) MyCommands.geometryCommand.setLocalScale(root.geometry, value) }
    }
}
