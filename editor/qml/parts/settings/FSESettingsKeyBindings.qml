import QtQuick
import QtQuick.Layouts

import editor

GridLayout {
    columns: 3
    columnSpacing: 5
    rowSpacing: 5

    FSEComboBox {
        Layout.alignment: Qt.AlignHCenter
        Layout.columnSpan: 3

        name: qsTr("Default settings")
        model: ListModel {
            ListElement { value: MyKeyBindings.KeyBindingsType.Custom; name: qsTr("Custom") }
            ListElement { value: MyKeyBindings.KeyBindingsType.Qwerty; name: "QWERTY" }
            ListElement { value: MyKeyBindings.KeyBindingsType.Azerty; name: "AZERTY" }
        }

        currentIndex: MyKeyBindings.current
        onActivated: MyKeyBindings.current = currentIndex
    }

    FSEText {
        Layout.alignment: Qt.AlignRight

        text: qsTr("Forward")
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
        Layout.alignment: Qt.AlignRight

        text: qsTr("Backward")
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
        Layout.alignment: Qt.AlignRight

        text: qsTr("Left")
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
        Layout.alignment: Qt.AlignRight

        text: qsTr("Right")
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
        Layout.alignment: Qt.AlignRight

        text: qsTr("Up")
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
        Layout.alignment: Qt.AlignRight

        text: qsTr("Down")
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.down1)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.down1 = key }
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.down2)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.down2 = key }
    }

    FSEText {
        Layout.alignment: Qt.AlignRight

        text: qsTr("Sprint")
    }
    FSEKeyButton {
        text: MyKeyBindings.toString(MyKeyBindings.keyBindings.sprint)
        onKeyPressed: (key)=> { MyKeyBindings.keyBindings.sprint = key }
    }
    Item { }
}
