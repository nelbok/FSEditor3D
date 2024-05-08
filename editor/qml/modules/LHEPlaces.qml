import QtQuick
import QtQuick.Layouts

import LHEditor

LHEModule {
    property MyPlace current: null

    id: root
    title: qsTr("Places")

    selection: LHEList {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        model: (MyProject) ? MyProject.places : null
        onCurrentDataChanged: (data) => {
                                  root.current = data
                                  var name = (data) ? data.name : "NULL"
                                  console.log("Place chosen: " + name);
                              }
    }
}
