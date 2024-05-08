import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

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

    placement: ColumnLayout {
        TextField {
            text: (root.myData) ? root.myData.name : "-"
            onEditingFinished: { if (root.myData) root.myData.name = text }
            enabled: root.myData
        }
        LHEPositionField {
            position: (root.myData) ? root.myData.position : Qt.vector3d(0, 0, 0)
            onPositionEdited: (position) => { if (root.myData) root.myData.position = position }
            enabled: root.myData
        }
        LHERotationField {
            rotation: (root.myData) ? root.myData.rotation : Qt.vector2d(0, 0)
            onRotationEdited: (rotation) => { if (root.myData) root.myData.camera = rotation }
            enabled: root.myData
        }
    }

    partA: ColumnLayout {
        LHEColorField {
            color: (root.myData) ? root.myData.hair : "transparent"
            onColorEdited: (color) => { if (root.myData) root.myData.hair = color }
            enabled: root.myData
        }
        LHEColorField {
            color: (root.myData) ? root.myData.skin : "transparent"
            onColorEdited: (color) => { if (root.myData) root.myData.skin = color }
            enabled: root.myData
        }
        LHEColorField {
            color: (root.myData) ? root.myData.clothes : "transparent"
            onColorEdited: (color) => { if (root.myData) root.myData.clothes = color }
            enabled: root.myData
        }
    }

    partB: ColumnLayout {
        SpinBox {
            implicitWidth: 200

            from: 135
            to: 200
            editable: true
            value: (root.myData) ? root.myData.height : 0
            onValueChanged: { if (root.myData) root.myData.height = value }
            enabled: root.myData
        }
        ComboBox {
            implicitWidth: 200

            valueRole: "value"
            textRole: "text"
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
            currentIndex: (root.myData) ? indexOfValue(root.myData.species) : -1
            onCurrentIndexChanged: { if (root.myData) root.myData.species = valueAt(currentIndex) }
            enabled: root.myData
        }
        ComboBox {
            implicitWidth: 200

            valueRole: "value"
            textRole: "text"
            model: [
                { value: MyCharacter.Gender.Male, text: "Male" },
                { value: MyCharacter.Gender.Female, text: "Female"},
            ]
            currentIndex: (root.myData) ? indexOfValue(root.myData.gender) : -1
            onCurrentIndexChanged: { if (root.myData) root.myData.gender = valueAt(currentIndex) }
            enabled: root.myData
        }
    }
}
