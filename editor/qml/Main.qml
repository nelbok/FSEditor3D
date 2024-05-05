import QtQuick
import QtQuick.Layouts

import LHEditor

Window {
    id: root
    width: 1280
    height: 768
    minimumWidth: 1280
    minimumHeight: 768
    maximumWidth: 1280
    maximumHeight: 768
    visible: true

    Rectangle {
        anchors.fill: parent
        color: "#CCCCCC"

        RowLayout {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 10
            spacing: 10

            LHEMenu {
                id: menuForm
                myData: MyProject
            }

            LHEProject {
                id: projectForm
                myData: MyProject
                onCurrentPlaceChanged: (place) => { placeForm.myData = place }
            }

            LHEPlace {
                id: placeForm
                // myData: MyProject.map
                // onAddNpc: MyProject.addNpc()
                // onRemoveNpc: (npc) => { if (npc) MyProject.removeNpc(npc) }
                // onCurrentNpcChanged: (npc) => { npcForm.myData = npc }
            }

            // LHECharacter {
            //     id: npcForm
            // }
        }
    }
}
