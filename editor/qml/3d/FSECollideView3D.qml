import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick3D.Physics

import editor

// https://doc.qt.io/qt-6/qtquick3dphysics-units.html
// Qt Quick 3D Unit: cm Angle: degree
View3D {
    id: view3D
    PhysicsWorld {
        id: physicsWorld
        running: MySelection.currentType !== MySelection.Type.Settings
        scene: view3D.scene
        forceDebugDraw: MyPreview.isDebugMode
    }

    environment: SceneEnvironment {
        clearColor: "skyblue"
        backgroundMode: SceneEnvironment.Color

        InfiniteGrid {
            gridInterval: 100 // 1meter
        }
    }

    // A light like the sun
    DirectionalLight {
        eulerRotation.x: -30
        eulerRotation.y: -70
        castsShadow: true
        shadowMapQuality: Light.ShadowMapQualityVeryHigh
    }

    // Camera with its controller to make it easy to move around the scene
    CharacterController {
        id: character

        collisionShapes: CapsuleShape {
            diameter: 50
            height: 50
        }

        gravity: (view3D.visible && MyPreview.isGravityEnabled ) ? physicsWorld.gravity : Qt.vector3d(0,0,0)
        movement: controller.movement

        onPositionChanged: { MyPreview.cameraPosition = position }
        eulerRotation.y: controller.rotation.y
        PerspectiveCamera {
            eulerRotation.x: controller.rotation.x
        }
    }
    FSECollideController3D {
        id: controller
        rotation: MyPreview.cameraRotation
        onRotationChanged: { MyPreview.cameraRotation = rotation }
    }

    Connections {
        target: MyPreview
        function onCameraPositionUpdated() {
            if (!MyPreview.isGravityEnabled)
                character.teleport(MyPreview.cameraPosition)
        }
    }

    Component.onCompleted: {
        character.position = MyPreview.cameraPosition
    }
}
