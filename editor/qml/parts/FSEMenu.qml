import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    width: 1100
    height: 50

    MouseArea {
        anchors.fill: parent

        // Avoid 3D View to catch mouse events
        preventStealing: true

        onClicked: MySelection.currentType = MySelection.Type.None
    }

    RowLayout {
        anchors.centerIn: parent
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

        ColumnLayout {
            spacing: 0
            width: 140
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
            width: 140
            height: 20

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
