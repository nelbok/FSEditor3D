import QtQuick
import QtQuick.Layouts

import editor

LHEModule {
    property MyCharacter myData: null

    id: root
    title: qsTr("Characters")

    MySelectionManager {
        id: mng
        model: MyModels.characterModel
        onCurrentDataChanged: root.myData = currentData
    }

    selection: LHEList {
        model: mng.model
        currentIndex: mng.currentIndex
        removeEnabled: mng.currentData && !mng.currentData.hasRef
        duplicateEnabled: mng.currentData

        onCreateClicked: { MyCommands.projectCommand.createCharacter() }
        onRemoveClicked: { MyCommands.projectCommand.removeCharacter(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateCharacter(mng.currentData) }
        onItemClicked: (index) => { mng.currentIndex = index }
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
            onColorEdited: (color) => { if (root.myData) MyCommands.characterCommand.setHair(root.myData, color) }
        }
        LHEColorField {
            name: qsTr("Skin")
            color: (root.myData) ? root.myData.skin : "gray"
            onColorEdited: (color) => { if (root.myData) MyCommands.characterCommand.setSkin(root.myData, color) }
        }
        LHEColorField {
            name: qsTr("Clothes")
            color: (root.myData) ? root.myData.clothes : "gray"
            onColorEdited: (color) => { if (root.myData) MyCommands.characterCommand.setClothes(root.myData, color) }
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
            onValueChanged: { if (root.myData) MyCommands.characterCommand.setHeight(root.myData, value) }
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
            onActivated: { if (root.myData) MyCommands.characterCommand.setSpecies(root.myData, valueAt(currentIndex)) }
        }
        LHEComboBox {
            name: qsTr("Gender")
            model: [
                { uuid: MyCharacter.Gender.Male, name: qsTr("Male") },
                { uuid: MyCharacter.Gender.Female, name: qsTr("Female") },
            ]
            currentIndex: (root.myData) ? indexOfValue(root.myData.gender) : -1
            onActivated: { if (root.myData) MyCommands.characterCommand.setGender(root.myData, valueAt(currentIndex)) }
        }
    }
}
