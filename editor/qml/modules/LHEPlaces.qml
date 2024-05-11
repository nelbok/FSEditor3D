import QtQuick
import QtQuick.Layouts

import editor

LHEModule {
    property MyPlace myData: null

    id: root
    title: qsTr("Places")

    selection: LHEList {
        model: (MyProject) ? MyProject.places : null
        onCreateClicked: { if (MyProject) MyProject.createPlace() }
        onRemoveClicked: (data) => { if (MyProject) MyProject.removePlace(data) }
        onDuplicateClicked: (data) => { if (MyProject) MyProject.duplicatePlace(data) }
        onCurrentDataChanged: (data) => { root.myData = data }
    }

    placement: LHEEntity {
        entity: root.myData
    }
}
