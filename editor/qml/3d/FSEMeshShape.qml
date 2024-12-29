import QtQuick
import QtQuick3D.Physics

import editor

TriangleMeshShape {
    property MyGeometry geometry: null
    property vector3d offset: Qt.vector3d(0, 0, 0)

    // Seems to have a bug around position and scale.
    // Like it is scaled before applying the scale...
    position.x: (offset.x + (geometry ? geometry.globalPosition.x : 0)) / scale.x
    position.y: (offset.y + (geometry ? geometry.globalPosition.y : 0)) / scale.y
    position.z: (offset.z + (geometry ? geometry.globalPosition.z : 0)) / scale.z
    eulerRotation: geometry ? geometry.globalRotation : Qt.vector3d(0, 0, 0)
    scale: geometry ? geometry.globalScale : Qt.vector3d(1, 1, 1)
}
