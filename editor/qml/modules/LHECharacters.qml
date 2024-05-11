import QtQuick
import QtQuick.Layouts

import editor

LHEModule {
    property MyCharacter myData: null

    id: root
    title: qsTr("Characters")

    selection: LHEList {
        model: (MyProject) ? MyProject.characters : null
        onCreateClicked: { if (MyProject) MyProject.createCharacter() }
        onRemoveClicked: (data) => { if (MyProject) MyProject.removeCharacter(data) }
        onDuplicateClicked: (data) => { if (MyProject) MyProject.duplicateCharacter(data) }
        onCurrentDataChanged: (data) => { root.myData = data }
    }

    placement: LHEPlacement {
        placement: root.myData
    }

    partA: ColumnLayout {
        spacing: 5
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
        spacing: 5
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
                { uuid: MyCharacter.Species.Human, name: qsTr("Human") },

                // Demi human
                { uuid: MyCharacter.Species.Fox, name: qsTr("Fox") },
                { uuid: MyCharacter.Species.Cat, name: qsTr("Cat") },
                { uuid: MyCharacter.Species.Dog, name: qsTr("Dog") },
                { uuid: MyCharacter.Species.Bun, name: qsTr("Bun") },
                { uuid: MyCharacter.Species.Rat, name: qsTr("Rat") },

                // Monster
                { uuid: MyCharacter.Species.Goblin, name: qsTr("Goblin") },
                { uuid: MyCharacter.Species.Ogre, name: qsTr("Ogre") },
                { uuid: MyCharacter.Species.Orc, name: qsTr("Orc") },
                { uuid: MyCharacter.Species.Troll, name: qsTr("Troll") },
                { uuid: MyCharacter.Species.Lizard, name: qsTr("Lizard") },
            ]
            currentIndex: { (root.myData) ? indexOfValue(root.myData.species) : -1 }
            onActivated: { if (root.myData) root.myData.species = valueAt(currentIndex) }
        }
        LHEComboBox {
            name: qsTr("Gender")
            model: [
                { uuid: MyCharacter.Gender.Male, name: qsTr("Male") },
                { uuid: MyCharacter.Gender.Female, name: qsTr("Female") },
            ]
            currentIndex: (root.myData) ? indexOfValue(root.myData.gender) : -1
            onActivated: { if (root.myData) root.myData.gender = valueAt(currentIndex) }
        }
    }
}
