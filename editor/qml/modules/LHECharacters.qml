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
                { value: MyCharacter.Species.Human, text: "Human" },

                // Demi human
                { value: MyCharacter.Species.Fox, text: "Fox" },
                { value: MyCharacter.Species.Cat, text: "Cat" },
                { value: MyCharacter.Species.Dog, text: "Dog" },
                { value: MyCharacter.Species.Bun, text: "Bun" },
                { value: MyCharacter.Species.Rat, text: "Rat" },

                // Monster
                { value: MyCharacter.Species.Goblin, text: "Goblin" },
                { value: MyCharacter.Species.Ogre, text: "Ogre" },
                { value: MyCharacter.Species.Orc, text: "Orc" },
                { value: MyCharacter.Species.Troll, text: "Troll" },
                { value: MyCharacter.Species.Lizard, text: "Lizard" },
            ]
            currentIndex: { (root.myData) ? indexOfValue(root.myData.species) : -1 }
            onActivated: { if (root.myData) root.myData.species = valueAt(currentIndex) }
        }
        LHEComboBox {
            name: qsTr("Gender")
            model: [
                { value: MyCharacter.Gender.Male, text: "Male" },
                { value: MyCharacter.Gender.Female, text: "Female"},
            ]
            currentIndex: (root.myData) ? indexOfValue(root.myData.gender) : -1
            onActivated: { if (root.myData) root.myData.gender = valueAt(currentIndex) }
        }
    }
}
