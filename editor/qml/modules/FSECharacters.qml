import QtQuick
import QtQuick.Layouts

import editor

FSEModule {
    property MyCharacter myData: null

    id: root
    title: qsTr("Characters")

    MySelectionWrapper {
        id: mng
        model: MyModels.characterModel
        onCurrentDataChanged: root.myData = currentData
    }

    selection: FSEList {
        model: mng.model
        currentIndex: mng.currentIndex
        removeEnabled: mng.currentData && !mng.currentData.hasRef
        duplicateEnabled: mng.currentData

        onCreateClicked: { MyCommands.projectCommand.createCharacter() }
        onRemoveClicked: { MyCommands.projectCommand.removeCharacter(mng.currentData) }
        onDuplicateClicked: { MyCommands.projectCommand.duplicateCharacter(mng.currentData) }
        onItemClicked: (index) => { mng.currentIndex = index }
    }

    placement: FSEPlacement {
        placement: root.myData
        filters: {
            "type": MyModel.Type.Character,
        }
    }

    partA: ColumnLayout {
        spacing: 5
        enabled: root.myData
        FSEColorField {
            name: qsTr("Hair")
            color: (root.myData) ? root.myData.hair : "gray"
            onColorEdited: (color) => { if (root.myData) MyCommands.characterCommand.setHair(root.myData, color) }
        }
        FSEColorField {
            name: qsTr("Skin")
            color: (root.myData) ? root.myData.skin : "gray"
            onColorEdited: (color) => { if (root.myData) MyCommands.characterCommand.setSkin(root.myData, color) }
        }
        FSEColorField {
            name: qsTr("Clothes")
            color: (root.myData) ? root.myData.clothes : "gray"
            onColorEdited: (color) => { if (root.myData) MyCommands.characterCommand.setClothes(root.myData, color) }
        }
    }

    partB: ColumnLayout {
        spacing: 5
        enabled: root.myData
        FSESpinBox {
            name: qsTr("Height")
            from: 135
            to: 200
            value: (root.myData) ? root.myData.height : 0
            onValueChanged: { if (root.myData) MyCommands.characterCommand.setHeight(root.myData, value) }
        }
        FSEComboBox {
            name: qsTr("Species")
            model: ListModel {
                ListElement { uuid: MyCharacter.Species.Human; name: qsTr("Human") }

                // Demi human
                ListElement { uuid: MyCharacter.Species.Fox; name: qsTr("Fox") }
                ListElement { uuid: MyCharacter.Species.Cat; name: qsTr("Cat") }
                ListElement { uuid: MyCharacter.Species.Dog; name: qsTr("Dog") }
                ListElement { uuid: MyCharacter.Species.Bun; name: qsTr("Bun") }
                ListElement { uuid: MyCharacter.Species.Rat; name: qsTr("Rat") }

                // Monster
                ListElement { uuid: MyCharacter.Species.Goblin; name: qsTr("Goblin") }
                ListElement { uuid: MyCharacter.Species.Ogre; name: qsTr("Ogre") }
                ListElement { uuid: MyCharacter.Species.Orc; name: qsTr("Orc") }
                ListElement { uuid: MyCharacter.Species.Troll; name: qsTr("Troll") }
                ListElement { uuid: MyCharacter.Species.Lizard; name: qsTr("Lizard") }
            }
            currentIndex: { (root.myData) ? indexOfValue(root.myData.species) : -1 }
            onActivated: { if (root.myData) MyCommands.characterCommand.setSpecies(root.myData, valueAt(currentIndex)) }
        }
        FSEComboBox {
            name: qsTr("Gender")
            model: ListModel {
                ListElement { uuid: MyCharacter.Gender.Male; name: qsTr("Male") }
                ListElement { uuid: MyCharacter.Gender.Female; name: qsTr("Female") }
            }
            currentIndex: (root.myData) ? indexOfValue(root.myData.gender) : -1
            onActivated: { if (root.myData) MyCommands.characterCommand.setGender(root.myData, valueAt(currentIndex)) }
        }
    }
}
