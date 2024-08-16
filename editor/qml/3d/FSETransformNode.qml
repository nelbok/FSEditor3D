import QtQuick
import QtQuick3D

import editor

Node {
    property MyGeometry geometry: null

    id: node

    position: (node.geometry) ? node.geometry.globalPosition : Qt.vector3d(0, 0, 0)
    eulerRotation: (node.geometry) ? node.geometry.globalRotation : Qt.vector3d(0, 0, 0)
    scale: (node.geometry) ? node.geometry.globalScale : Qt.vector3d(1, 1, 1)
}
