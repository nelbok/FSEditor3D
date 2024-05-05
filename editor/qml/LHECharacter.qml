import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import "common"
import LHEditor

Rectangle {
    property MyCharacter myData: null;

    id: root
    border.color: "black"
    border.width: 2
    color: "#6666AA"
    radius: 5

    implicitHeight: layout.implicitHeight + 20
    implicitWidth: layout.implicitWidth + 20

    GridLayout {
        id: layout
        anchors.fill: parent
        anchors.margins: 10
        columns: 2

        Text {
            text: "Name:"
        }
        TextField {
            text: (root.myData) ? root.myData.name : "-"
            onEditingFinished: { if (root.myData) root.myData.name = text }
            enabled: root.myData
        }

        Text {
            text: "Position:"
        }
        LHEPositionField {
            position: (root.myData) ? root.myData.position : Qt.vector3d(0, 0, 0)
            onPositionEdited: (position) => { if (root.myData) root.myData.position = position }
            enabled: root.myData
        }

        Text {
            text: "Camera:"
        }
        LHERotationField {
            rotation: (root.myData) ? root.myData.camera : Qt.vector2d(0, 0)
            onRotationEdited: (rotation) => { if (root.myData) root.myData.camera = rotation }
            enabled: root.myData
        }

        Text {
            text: "Hair color:"
        }
        LHEColorField {
            color: (root.myData) ? root.myData.hair : "transparent"
            onColorEdited: (color) => { if (root.myData) root.myData.hair = color }
            enabled: root.myData
        }

        Text {
            text: "Skin color:"
        }
        LHEColorField {
            color: (root.myData) ? root.myData.skin : "transparent"
            onColorEdited: (color) => { if (root.myData) root.myData.skin = color }
            enabled: root.myData
        }

        Text {
            text: "Clothes color:"
        }
        LHEColorField {
            color: (root.myData) ? root.myData.clothes : "transparent"
            onColorEdited: (color) => { if (root.myData) root.myData.clothes = color }
            enabled: root.myData
        }

        Text {
            text: "Height:"
        }
        SpinBox {
            implicitWidth: 200

            from: 135
            to: 200
            editable: true
            value: (root.myData) ? root.myData.height : 0
            onValueChanged: { if (root.myData) root.myData.height = value }
            enabled: root.myData
        }

        Text {
            text: "Species:"
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

        Text {
            text: "Gender:"
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
