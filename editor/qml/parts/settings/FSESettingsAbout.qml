import QtQuick
import QtQuick.Layouts

import editor

ColumnLayout {
    spacing: 5

    FSEText {
        text: MyManager.about.name
        font.bold: MyStyles.style.titleFont.bold
        font.italic: MyStyles.style.titleFont.italic
        font.pointSize: MyStyles.style.titleFont.pointSize
    }

    Item {
        Layout.preferredHeight: 10
    }

    FSEText {
        text: MyManager.about.description
    }

    Item {
        Layout.preferredHeight: 20
    }

    FSEText {
        text: qsTr("Version:") + " " + MyManager.about.version
    }

    FSEText {
        text: qsTr("Qt version:") + " " + MyManager.about.qtVersion
    }

    Item {
        Layout.preferredHeight: 20
    }

    FSEText {
        text: qsTr("Github:") + " " + MyManager.about.github
    }

    FSEText {
        text: qsTr("Discord:") + " " + MyManager.about.discord
    }

    FSEText {
        text: qsTr("Twitter:") + " " + MyManager.about.twitter
    }

    Item {
        Layout.preferredHeight: 20
    }

    FSEText {
        text: MyManager.about.copyright
    }
}
