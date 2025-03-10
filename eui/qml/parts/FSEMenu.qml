import QtQuick
import QtQuick.Layouts

import eui

FSERectangle {
    id: root

    height: 50

    MouseArea {
        anchors.fill: parent

        // Avoid 3D View to catch mouse events
        preventStealing: true

        onClicked: MySelection.currentType = MySelection.Type.None
    }

    RowLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 40
        spacing: 20

        FSEButton {
            text: qsTr("Project")
            selected: MySelection.currentType === MySelection.Type.Project
            onClicked: MySelection.currentType = MySelection.Type.Project
        }

        FSEButton {
            text: qsTr("Models")
            selected: MySelection.currentType === MySelection.Type.Models
            onClicked: MySelection.currentType = MySelection.Type.Models
        }

        FSEButton {
            text: qsTr("Places")
            selected: MySelection.currentType === MySelection.Type.Places
            onClicked: MySelection.currentType = MySelection.Type.Places
        }

        FSEButton {
            text: qsTr("Objects")
            selected: MySelection.currentType === MySelection.Type.Objects
            onClicked: MySelection.currentType = MySelection.Type.Objects
        }

        FSEButton {
            text: qsTr("Links")
            selected: MySelection.currentType === MySelection.Type.Links
            onClicked: MySelection.currentType = MySelection.Type.Links
        }

        FSEButton {
            text: qsTr("Entry points")
            selected: MySelection.currentType === MySelection.Type.EntryPoints
            onClicked: MySelection.currentType = MySelection.Type.EntryPoints
        }
    }

    RowLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 40
        spacing: 20

        ColumnLayout {
            spacing: 0
            implicitWidth: 140
            Text {
                Layout.fillWidth: true

                text: "Version " + MyManager.about.version
                color: MyStyles.style.foreground.normal
                font.bold: MyStyles.style.copyrightFont.bold
                font.italic: MyStyles.style.copyrightFont.italic
                font.pointSize: MyStyles.style.copyrightFont.pointSize

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                Layout.fillWidth: true

                text: MyManager.about.copyright
                color: MyStyles.style.foreground.normal
                font.bold: MyStyles.style.copyrightFont.bold
                font.italic: MyStyles.style.copyrightFont.italic
                font.pointSize: MyStyles.style.copyrightFont.pointSize

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Item {
            implicitWidth: 140
            implicitHeight: 20

            visible: root.width >= 1280

            RowLayout {
                anchors.horizontalCenter: parent.horizontalCenter

                height: 20
                spacing: 20
                FSEIconButton {
                    imageHeight: 20
                    source: "qrc:/social/" + MyStyles.style.icons.github + ".svg"
                    onClicked: Qt.openUrlExternally(MyManager.about.github)
                }
                FSEIconButton {
                    imageHeight: 20
                    source: "qrc:/social/" + MyStyles.style.icons.discord + ".svg"
                    onClicked: Qt.openUrlExternally(MyManager.about.discord)
                }
                FSEIconButton {
                    imageHeight: 20
                    source: "qrc:/social/" + MyStyles.style.icons.twitter + ".svg"
                    onClicked: Qt.openUrlExternally(MyManager.about.twitter)
                }
            }
        }
    }
}
