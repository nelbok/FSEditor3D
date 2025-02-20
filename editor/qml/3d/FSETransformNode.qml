import QtQuick
import QtQuick3D
import QtQuick3D.Physics

import editor

StaticRigidBody {
    property MyGeometry geometry: null
    property vector3d offset: Qt.vector3d(0, 0, 0)
    property alias innerNode: innerNode

    id: node

    Node {
        id: innerNode
        position.x: node.offset.x + ((node.geometry) ? node.geometry.globalPosition.x : 0)
        position.y: node.offset.y + ((node.geometry) ? node.geometry.globalPosition.y : 0)
        position.z: node.offset.z + ((node.geometry) ? node.geometry.globalPosition.z : 0)
        eulerRotation: (node.geometry) ? node.geometry.globalRotation : Qt.vector3d(0, 0, 0)
        scale: (node.geometry) ? node.geometry.globalScale : Qt.vector3d(1, 1, 1)
    }
}
