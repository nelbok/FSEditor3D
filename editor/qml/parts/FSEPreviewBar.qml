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
            source: "qrc:/preview/" + MyStyles.style.centerOn + ".svg"
            onClicked: MyPreview.centerOnCurrent()
        }

        FSEToolButton {
            source: "qrc:/preview/" + (MyPreview.areOtherDatasVisible ? MyStyles.style.othersOn : MyStyles.style.othersOff) + ".svg"
            onClicked: MyPreview.switchOtherDatasVisible()
        }

        FSEToolButton {
            source: "qrc:/preview/" + (MyPreview.areOriginsVisible ? MyStyles.style.originOn : MyStyles.style.originOff) + ".svg"
            onClicked: MyPreview.switchOriginsVisible()
        }

        FSEToolButton {
            source: "qrc:/preview/" + (MyPreview.isWorldMapVisible ? MyStyles.style.worldMapOn : MyStyles.style.worldMapOff) + ".svg"
            onClicked: MyPreview.switchWorldMapVisible()
        }
    }
}
