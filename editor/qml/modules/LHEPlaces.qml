import QtQuick
import QtQuick.Layouts

import LHEditor

LHEModule {
    property MyPlace myData: null

    id: root
    title: qsTr("Places")

    selection: LHEList {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        model: (MyProject) ? MyProject.places : null
        onCurrentDataChanged: (data) => { root.myData = data }
    }

    placement: LHEEntity {
        entity: root.myData
    }
}
