import QtQuick
import QtQuick.Layouts

import editor

ColumnLayout {
    property MyGeometry geometry: null

    id: root

    spacing: 5
    enabled: root.geometry

    FSEVector3DField {
        name: qsTr("Position")
        value: (root.geometry) ? root.geometry.position : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.geometry) MyCommands.geometryCommand.setPosition(root.geometry, value) }
    }

    FSEVector3DField {
        name: qsTr("Rotation")
        value: (root.geometry) ? root.geometry.rotation : Qt.vector3d(0, 0, 0)
        onEditingFinished: (value) => { if (root.geometry) MyCommands.geometryCommand.setRotation(root.geometry, value) }
    }

    FSEVector3DField {
        name: qsTr("Scale")
        value: (root.geometry) ? root.geometry.scale : Qt.vector3d(1, 1, 1)
        onEditingFinished: (value) => { if (root.geometry) MyCommands.geometryCommand.setScale(root.geometry, value) }
    }
}
