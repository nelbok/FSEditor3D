import QtQuick
import QtQuick.Layouts

import eui

ColumnLayout {
    property MyEntity entity: null

    id: root

    spacing: 5
    enabled: root.entity

    FSEButton {
        Layout.fillWidth: true

        text: (root.entity) ? ((timer.running) ? qsTr("Copied!") : root.entity.uuid) : "-"
        onClicked: {
            if (root.entity && !timer.running) {
                timer.start()
                MyInterface.setClipboardText(root.entity.uuid)
            }
        }

        Timer {
            id: timer
            interval: 800
        }
    }

    FSETextField {
        name: qsTr("Name")
        value: (root.entity) ? root.entity.name : "-"
        placeholder: qsTr("Enter something...")
        onEditingFinished: { if (root.entity) MyCommands.entityCommand.setName(root.entity, value) }
    }
}
