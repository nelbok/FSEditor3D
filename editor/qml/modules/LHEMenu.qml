import QtQuick
import QtQuick.Layouts

import editor

LHERectangle {
    enum ModuleType {
        Project,
        Models,
        Places,
        Characters,
        Links,
        None
    }
    property int selected: LHEMenu.ModuleType.None

    id: root
    width: 1100
    height: 50

    MouseArea {
        anchors.fill: parent
        onClicked: root.selected = LHEMenu.ModuleType.None
    }

    RowLayout {
        anchors.centerIn: parent
        spacing: 20

        LHEButton {
            id: project

            text: qsTr("Project")
            selected: root.selected === LHEMenu.ModuleType.Project
            onClicked: root.selected = LHEMenu.ModuleType.Project
        }

        LHEButton {
            id: models

            text: qsTr("Models")
            selected: root.selected === LHEMenu.ModuleType.Models
            onClicked: root.selected = LHEMenu.ModuleType.Models
        }

        LHEButton {
            id: places

            text: qsTr("Places")
            selected: root.selected === LHEMenu.ModuleType.Places
            onClicked: root.selected = LHEMenu.ModuleType.Places
        }

        LHEButton {
            id: characters

            text: qsTr("Characters")
            selected: root.selected === LHEMenu.ModuleType.Characters
            onClicked: root.selected = LHEMenu.ModuleType.Characters
        }

        LHEButton {
            id: links

            text: qsTr("Links")
            selected: root.selected === LHEMenu.ModuleType.Links
            onClicked: root.selected = LHEMenu.ModuleType.Links
        }

        ColumnLayout {
            spacing: 0
            width: 140
            Text {
                Layout.fillWidth: true

                text: "Version " + MyController.about.version
                color: LHEStyle.foreground.normal
                font.bold: LHEStyle.copyrightFont.bold
                font.italic: LHEStyle.copyrightFont.italic
                font.pointSize: LHEStyle.copyrightFont.pointSize

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                Layout.fillWidth: true

                text: MyController.about.copyright
                color: LHEStyle.foreground.normal
                font.bold: LHEStyle.copyrightFont.bold
                font.italic: LHEStyle.copyrightFont.italic
                font.pointSize: LHEStyle.copyrightFont.pointSize

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Item {
            width: 140
            height: 20

            RowLayout {
                anchors.horizontalCenter: parent.horizontalCenter

                height: 20
                spacing: 20
                LHEIconButton {
                    imageHeight: 20
                    source: "qrc:/social/github.svg"
                    onClicked: Qt.openUrlExternally(MyController.about.github)
                }
                LHEIconButton {
                    imageHeight: 20
                    source: "qrc:/social/discord.svg"
                    onClicked: Qt.openUrlExternally(MyController.about.discord)
                }
                LHEIconButton {
                    imageHeight: 20
                    source: "qrc:/social/twitter.svg"
                    onClicked: Qt.openUrlExternally(MyController.about.twitter)
                }
            }
        }
    }
}
