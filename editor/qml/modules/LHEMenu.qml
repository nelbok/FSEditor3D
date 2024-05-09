import QtQuick
import QtQuick.Layouts

import LHEditor

LHERectangle {
    enum ModuleType {
        Project,
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
        spacing: 41.6

        Text {
            text: MyAbout.name
            color: LHEStyle.foreground.normal
            font.bold: LHEStyle.titleFont.bold
            font.italic: LHEStyle.titleFont.italic
            font.pointSize: LHEStyle.titleFont.pointSize
        }

        LHEButton {
            id: project

            text: qsTr("Project")
            selected: root.selected === LHEMenu.ModuleType.Project
            onClicked: root.selected = LHEMenu.ModuleType.Project
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

                text: "Version " + MyAbout.version
                color: LHEStyle.foreground.normal
                font.bold: LHEStyle.copyrightFont.bold
                font.italic: LHEStyle.copyrightFont.italic
                font.pointSize: LHEStyle.copyrightFont.pointSize

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                Layout.fillWidth: true

                text: MyAbout.copyright
                color: LHEStyle.foreground.normal
                font.bold: LHEStyle.copyrightFont.bold
                font.italic: LHEStyle.copyrightFont.italic
                font.pointSize: LHEStyle.copyrightFont.pointSize

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
