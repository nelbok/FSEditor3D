import QtQuick

import eui

Item {
    property vector2d rotation: Qt.vector2d(0, 0)
    property vector3d movement: Qt.vector3d(data.sideSpeed, data.upSpeed, data.forwardSpeed)

    id: root
    implicitWidth: parent.width
    implicitHeight: parent.height

    DragHandler {
        id: dragHandler
        target: null
        onCentroidChanged: {
            data.currentPos = Qt.vector2d(centroid.position.x, centroid.position.y)
        }
        onActiveChanged: {
            if (active) {
                root.forceActiveFocus()
                data.currentPos = Qt.vector2d(centroid.position.x, centroid.position.y)
                data.lastPos = data.currentPos
            }

            data.useMouse = active
        }
    }

    Timer {
        interval: 16
        repeat: true
        running: data.useMouse
        onTriggered: data.processInput()
    }

    Keys.onPressed: (event) => { data.processKeyPressed(event) }
    Keys.onReleased: (event) => { data.processKeyReleased(event) }

    QtObject {
        id: data

        property real speed: (sprint ? 3 : 1) * 500
        property real sideSpeed: (left ? -1 : right ? 1 : 0) * speed
        property real forwardSpeed: (forward ? -1 : backward ? 1 : 0) * speed
        property real upSpeed: (down ? -1 : up ? 1 : 0) * speed

        property bool forward: false
        property bool backward: false
        property bool left: false
        property bool right: false
        property bool down: false
        property bool up: false
        property bool sprint: false

        property vector2d lastPos: Qt.vector2d(0, 0)
        property vector2d currentPos: Qt.vector2d(0, 0)
        property bool useMouse: false

        function processKeyPressed(event) {
            switch (event.key) {
            case MyKeyBindings.keyBindings.forward1:
            case MyKeyBindings.keyBindings.forward2:
                forward = true
                break;
            case MyKeyBindings.keyBindings.backward1:
            case MyKeyBindings.keyBindings.backward2:
                backward = true
                break;
            case MyKeyBindings.keyBindings.left1:
            case MyKeyBindings.keyBindings.left2:
                left = true
                break;
            case MyKeyBindings.keyBindings.right1:
            case MyKeyBindings.keyBindings.right2:
                right = true
                break;
            case MyKeyBindings.keyBindings.up1:
            case MyKeyBindings.keyBindings.up2:
                up = true;
                break;
            case MyKeyBindings.keyBindings.down1:
            case MyKeyBindings.keyBindings.down2:
                down = true;
                break;
            case MyKeyBindings.keyBindings.sprint:
                sprint = true;
                break;
            }
        }

        function processKeyReleased(event) {
            switch (event.key) {
            case MyKeyBindings.keyBindings.forward1:
            case MyKeyBindings.keyBindings.forward2:
                forward = false
                break;
            case MyKeyBindings.keyBindings.backward1:
            case MyKeyBindings.keyBindings.backward2:
                backward = false
                break;
            case MyKeyBindings.keyBindings.left1:
            case MyKeyBindings.keyBindings.left2:
                left = false
                break;
            case MyKeyBindings.keyBindings.right1:
            case MyKeyBindings.keyBindings.right2:
                right = false
                break;
            case MyKeyBindings.keyBindings.up1:
            case MyKeyBindings.keyBindings.up2:
                up = false;
                break;
            case MyKeyBindings.keyBindings.down1:
            case MyKeyBindings.keyBindings.down2:
                down = false;
                break;
            case MyKeyBindings.keyBindings.sprint:
                sprint = false;
                break;
            }
        }

        function processInput() {
            if (useMouse) {
                root.rotation.x += (lastPos.y - currentPos.y) * 0.25
                root.rotation.y += (lastPos.x - currentPos.x) * 0.25
                lastPos = currentPos
            }
        }
    }
}
