import QtQuick
import QtQuick.Layouts

import LHEditor

LHEModule {
    property MyCharacter myData: null

    id: root
    title: qsTr("Characters")

    selection: LHEList {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        model: (MyProject) ? MyProject.characters : null
        onCurrentDataChanged: (data) => { root.myData = data }
    }

    placement: LHEPlacement {
        placement: root.myData
    }

    partA: ColumnLayout {
        enabled: root.myData
        LHEColorField {
            name: qsTr("Hair")
            color: (root.myData) ? root.myData.hair : "gray"
            onColorEdited: (color) => { if (root.myData) root.myData.hair = color }
        }
        LHEColorField {
            name: qsTr("Skin")
            color: (root.myData) ? root.myData.skin : "gray"
            onColorEdited: (color) => { if (root.myData) root.myData.skin = color }
        }
        LHEColorField {
            name: qsTr("Clothes")
            color: (root.myData) ? root.myData.clothes : "gray"
            onColorEdited: (color) => { if (root.myData) root.myData.clothes = color }
        }
    }

    partB: ColumnLayout {
        enabled: root.myData
        LHESpinBox {
            name: qsTr("Height")
            from: 135
            to: 200
            value: (root.myData) ? root.myData.height : 0
            onValueChanged: { if (root.myData) root.myData.height = value }
        }
        LHEComboBox {
            name: qsTr("Species")
            model: [
                { uuid: MyCharacter.Species.Human, name: "Human" },

                // Demi human
                { uuid: MyCharacter.Species.Fox, name: "Fox" },
                { uuid: MyCharacter.Species.Cat, name: "Cat" },
                { uuid: MyCharacter.Species.Dog, name: "Dog" },
                { uuid: MyCharacter.Species.Bun, name: "Bun" },
                { uuid: MyCharacter.Species.Rat, name: "Rat" },

                // Monster
                { uuid: MyCharacter.Species.Goblin, name: "Goblin" },
                { uuid: MyCharacter.Species.Ogre, name: "Ogre" },
                { uuid: MyCharacter.Species.Orc, name: "Orc" },
                { uuid: MyCharacter.Species.Troll, name: "Troll" },
                { uuid: MyCharacter.Species.Lizard, name: "Lizard" },
            ]
            currentIndex: { (root.myData) ? indexOfValue(root.myData.species) : -1 }
            onActivated: { if (root.myData) root.myData.species = valueAt(currentIndex) }
        }
        LHEComboBox {
            name: qsTr("Gender")
            model: [
                { uuid: MyCharacter.Gender.Male, name: "Male" },
                { uuid: MyCharacter.Gender.Female, name: "Female"},
            ]
            currentIndex: (root.myData) ? indexOfValue(root.myData.gender) : -1
            onActivated: { if (root.myData) root.myData.gender = valueAt(currentIndex) }
        }
    }
}
