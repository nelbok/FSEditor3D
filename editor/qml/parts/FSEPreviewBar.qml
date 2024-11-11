import QtQuick
import QtQuick.Layouts

import editor

FSERectangle {
    width: 50
    height: 185

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        FSEToolButton {
            source: "qrc:/preview/" + MyStyles.style.icons.centerOn + ".svg"
            onClicked: MyPreview.centerOnCurrent()
        }

        FSEToolButton {
            source: "qrc:/preview/" + (MyPreview.areOtherDatasVisible ? MyStyles.style.icons.othersOn : MyStyles.style.icons.othersOff) + ".svg"
            onClicked: MyPreview.switchOtherDatasVisible()
        }

        FSEToolButton {
            source: "qrc:/preview/" + (MyPreview.areOriginsVisible ? MyStyles.style.icons.originOn : MyStyles.style.icons.originOff) + ".svg"
            onClicked: MyPreview.switchOriginsVisible()
        }

        FSEToolButton {
            source: "qrc:/preview/" + (MyPreview.isWorldMapVisible ? MyStyles.style.icons.worldMapOn : MyStyles.style.icons.worldMapOff) + ".svg"
            onClicked: MyPreview.switchWorldMapVisible()
        }
    }
}
