import QtQuick
import QtQuick.Layouts

import LHEditor

LHEModule {
    id: root
    title: qsTr("Links")

    selection: LHEList {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        model: (MyProject) ? MyProject.links : null
        onCurrentDataChanged: (data) => {
                                  var name = (data) ? data.name : "NULL"
                                  console.log("Link chosen: " + name);
                              }
    }
}
