import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    enum ModuleType {
        Project,
        Models,
        Places,
        Characters,
        Links,
        None
    }
    property int selected: FSEMenu.ModuleType.None

    id: root
    width: 1100
    height: 50

    MouseArea {
        anchors.fill: parent
        onClicked: root.selected = FSEMenu.ModuleType.None
    }

    RowLayout {
        anchors.centerIn: parent
        spacing: 20

        FSEButton {
            id: project

            text: qsTr("Project")
            selected: root.selected === FSEMenu.ModuleType.Project
            onClicked: root.selected = FSEMenu.ModuleType.Project
        }

        FSEButton {
            id: models

            text: qsTr("Models")
            selected: root.selected === FSEMenu.ModuleType.Models
            onClicked: root.selected = FSEMenu.ModuleType.Models
        }

        FSEButton {
            id: places

            text: qsTr("Places")
            selected: root.selected === FSEMenu.ModuleType.Places
            onClicked: root.selected = FSEMenu.ModuleType.Places
        }

        FSEButton {
            id: characters

            text: qsTr("Characters")
            selected: root.selected === FSEMenu.ModuleType.Characters
            onClicked: root.selected = FSEMenu.ModuleType.Characters
        }

        FSEButton {
            id: links

            text: qsTr("Links")
            selected: root.selected === FSEMenu.ModuleType.Links
            onClicked: root.selected = FSEMenu.ModuleType.Links
        }

        ColumnLayout {
            spacing: 0
            width: 140
            Text {
                Layout.fillWidth: true

                text: "Version " + MyManager.about.version
                color: MyManager.style.foreground.normal
                font.bold: MyManager.style.copyrightFont.bold
                font.italic: MyManager.style.copyrightFont.italic
                font.pointSize: MyManager.style.copyrightFont.pointSize

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                Layout.fillWidth: true

                text: MyManager.about.copyright
                color: MyManager.style.foreground.normal
                font.bold: MyManager.style.copyrightFont.bold
                font.italic: MyManager.style.copyrightFont.italic
                font.pointSize: MyManager.style.copyrightFont.pointSize

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
                FSEIconButton {
                    imageHeight: 20
                    source: "qrc:/social/github.svg"
                    onClicked: Qt.openUrlExternally(MyManager.about.github)
                }
                FSEIconButton {
                    imageHeight: 20
                    source: "qrc:/social/discord.svg"
                    onClicked: Qt.openUrlExternally(MyManager.about.discord)
                }
                FSEIconButton {
                    imageHeight: 20
                    source: "qrc:/social/twitter.svg"
                    onClicked: Qt.openUrlExternally(MyManager.about.twitter)
                }
            }
        }
    }
}
