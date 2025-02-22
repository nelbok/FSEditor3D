import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick3D.Physics

import eui

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
            height: MyPreview.height - diameter
        }

        gravity: (view3D.visible && MyPreview.isGravityEnabled ) ? physicsWorld.gravity : Qt.vector3d(0,0,0)
        movement: controller.movement

        onPositionChanged: {
            // Only update position when we are in Collide mode
            // to avoid flickering with the camera in Design mode
            if (MyPreview.viewMode === MyPreview.ViewMode.Design)
                return;

            MyPreview.cameraPosition = position
        }
        eulerRotation.y: controller.rotation.y
        PerspectiveCamera {
            y: MyPreview.height / 2 - 10
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
            // Only update position when we are in Design mode
            // to avoid flickering with the camera in Collide mode
            if (MyPreview.viewMode === MyPreview.ViewMode.Collide)
                return;

            character.teleport(MyPreview.cameraPosition)
        }
        function onTeleported() {
            // We don't need to update the camera when we are in Design mode
            // as onCameraPositionUpdated already does that
            if (MyPreview.viewMode === MyPreview.ViewMode.Design)
                return;

            character.teleport(MyPreview.cameraPosition)
        }
    }

    Component.onCompleted: {
        character.position = MyPreview.cameraPosition
    }
}
