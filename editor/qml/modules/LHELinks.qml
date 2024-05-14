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

            MyEntityModel {
                id: myModel
                model: (MyProject) ? MyProject.links : null
                currentData: (root.myData) ? root.myData.link : null
                onCurrentDataUpdated: { if (root.myData && root.myData.link !== currentData) root.myData.link = currentData }
            }

            model: myModel
            currentIndex: myModel.currentIndex
            onActivated: myModel.currentIndex = currentIndex
        }
    }
}
