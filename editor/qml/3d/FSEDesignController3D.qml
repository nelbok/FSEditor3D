import QtQuick
import QtQuick3D.Helpers

import editor

WasdController {
    function handleKeyPress(event)
    {
        switch (event.key) {
        case MyKeyBindings.keyBindings.forward1:
        case MyKeyBindings.keyBindings.forward2:
            forwardPressed();
            break;
        case MyKeyBindings.keyBindings.backward1:
        case MyKeyBindings.keyBindings.backward2:
            backPressed();
            break;
        case MyKeyBindings.keyBindings.left1:
        case MyKeyBindings.keyBindings.left2:
            leftPressed();
            break;
        case MyKeyBindings.keyBindings.right1:
        case MyKeyBindings.keyBindings.right2:
            rightPressed();
            break;
        case MyKeyBindings.keyBindings.up1:
        case MyKeyBindings.keyBindings.up2:
            upPressed();
            break;
        case MyKeyBindings.keyBindings.down1:
        case MyKeyBindings.keyBindings.down2:
            downPressed();
            break;
        case MyKeyBindings.keyBindings.sprint:
            shiftPressed();
            break;
        }
    }

    function handleKeyRelease(event)
    {
        switch (event.key) {
        case MyKeyBindings.keyBindings.forward1:
        case MyKeyBindings.keyBindings.forward2:
            forwardReleased();
            break;
        case MyKeyBindings.keyBindings.backward1:
        case MyKeyBindings.keyBindings.backward2:
            backReleased();
            break;
        case MyKeyBindings.keyBindings.left1:
        case MyKeyBindings.keyBindings.left2:
            leftReleased();
            break;
        case MyKeyBindings.keyBindings.right1:
        case MyKeyBindings.keyBindings.right2:
            rightReleased();
            break;
        case MyKeyBindings.keyBindings.up1:
        case MyKeyBindings.keyBindings.up2:
            upReleased();
            break;
        case MyKeyBindings.keyBindings.down1:
        case MyKeyBindings.keyBindings.down2:
            downReleased();
            break;
        case MyKeyBindings.keyBindings.sprint:
            shiftReleased();
            break;
        }
    }
}
