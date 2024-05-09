import QtQuick
import QtQuick.Layouts

import LHEditor

LHEModule {
    property MyLink myData: null

    id: root
    title: qsTr("Links")

    selection: LHEList {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        model: (MyProject) ? MyProject.links : null
        onCurrentDataChanged: (data) => { root.myData = data }
    }

    placement: LHEPlacement {
        placement: myData
    }
}
