import QtQuick
import QtQuick.Layouts

import editor

ColumnLayout {
    property MyEntity entity: null

    id: root

    spacing: 5
    enabled: root.entity

    FSETextField {
        name: qsTr("Name")
        value: (root.entity) ? root.entity.name : "-"
        placeholder: qsTr("Enter something...")
        onEditingFinished: { if (root.entity) MyCommands.entityCommand.setName(root.entity, value) }
    }
}
