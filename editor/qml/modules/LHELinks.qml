import QtQuick
import QtQuick.Layouts

import editor

LHEModule {
    property MyLink myData: null

    id: root
    title: qsTr("Links")

    selection: LHEList {
        model: (MyProject) ? MyProject.links : null
        onCreateClicked: { if (MyProject) MyProject.createLink() }
        onRemoveClicked: (data) => { if (MyProject) MyProject.removeLink(data) }
        onDuplicateClicked: (data) => { if (MyProject) MyProject.duplicateLink(data) }
        onCurrentDataChanged: (data) => { root.myData = data }
    }

    placement: LHEPlacement {
        placement: root.myData
    }

    partA: ColumnLayout {
        spacing: 5
        enabled: root.myData
        LHEComboBox {
            name: qsTr("Link")
            model: (MyProject) ? MyProject.links : null
            currentIndex: {
                if (root.myData && root.myData.link)
                    for(var i in MyProject.links) {
                        if (MyProject.links[i].uuid === root.myData.link.uuid)
                            return i
                    }
                return -1
            }
            onActivated: { if (root.myData) root.myData.link = model[currentIndex] }
        }
    }
}
