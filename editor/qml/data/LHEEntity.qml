import QtQuick
import QtQuick.Layouts

import editor

ColumnLayout {
    property MyEntity entity: null

    id: root

    spacing: 5
    enabled: root.entity

    LHETextField {
        name: qsTr("Id")
        value: (root.entity) ? root.entity.uuid : "-"
        enabled: false
    }

    LHETextField {
        name: qsTr("Name")
        value: (root.entity) ? root.entity.name : "-"
        placeholder: qsTr("Enter something...")
        onEditingFinished: { if (root.entity) root.entity.name = value }
    }
}
