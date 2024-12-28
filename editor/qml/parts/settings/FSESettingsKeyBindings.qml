import QtQuick
import QtQuick.Layouts

import editor

GridLayout {
    columns: 3
    columnSpacing: 5
    rowSpacing: 5

    FSEText {
        text: qsTr("Forward")
        Layout.alignment: Qt.AlignRight
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.forward1)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.forward1 = key }
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.forward2)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.forward2 = key }
    }

    FSEText {
        text: qsTr("Backward")
        Layout.alignment: Qt.AlignRight
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.backward1)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.backward1 = key }
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.backward2)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.backward2 = key }
    }

    FSEText {
        text: qsTr("Left")
        Layout.alignment: Qt.AlignRight
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.left1)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.left1 = key }
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.left2)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.left2 = key }
    }

    FSEText {
        text: qsTr("Right")
        Layout.alignment: Qt.AlignRight
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.right1)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.right1 = key }
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.right2)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.right2 = key }
    }

    FSEText {
        text: qsTr("Up")
        Layout.alignment: Qt.AlignRight
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.up1)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.up1 = key }
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.up2)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.up2 = key }
    }

    FSEText {
        text: qsTr("Down")
        Layout.alignment: Qt.AlignRight
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.down1)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.down1 = key }
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.down2)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.down2 = key }
    }
}
