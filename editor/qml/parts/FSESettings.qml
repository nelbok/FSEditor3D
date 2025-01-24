import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    enum SettingsType {
        Interface,
        KeyBindings,
        About
    }
    property int selected: FSESettings.SettingsType.Interface

    id: root

    width: 800
    height: 600

    FSEButton {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 10
        anchors.leftMargin: 10

        id: intefaceBtn
        text: qsTr("Interface")
        selected: root.selected === FSESettings.SettingsType.Interface
        onClicked: root.selected = FSESettings.SettingsType.Interface
    }

    FSEButton {
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: intefaceBtn.right

        id: keyboardBtn
        text: qsTr("Key bindings")
        selected: root.selected === FSESettings.SettingsType.KeyBindings
        onClicked: root.selected = FSESettings.SettingsType.KeyBindings
    }

    FSEButton {
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: keyboardBtn.right

        id: aboutBtn
        text: qsTr("About")
        selected: root.selected === FSESettings.SettingsType.About
        onClicked: root.selected = FSESettings.SettingsType.About
    }

    FSERectangle {
        anchors.top: intefaceBtn.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        id: content

        FSESettingsInterface {
            anchors.centerIn: content
            visible: root.selected === FSESettings.SettingsType.Interface
        }

        FSESettingsKeyBindings {
            anchors.centerIn: content
            visible: root.selected === FSESettings.SettingsType.KeyBindings
        }

        FSESettingsAbout {
            anchors.centerIn: content
            visible: root.selected === FSESettings.SettingsType.About
        }
    }
}
