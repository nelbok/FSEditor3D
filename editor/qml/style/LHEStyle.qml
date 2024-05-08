pragma Singleton
import QtQuick

QtObject {
    property QtObject window: QtObject {
        property color color: "#CCCCCC"
    }
    property QtObject button: QtObject {
        property color normal: "#6666AA"
        property color menu: "#CCCCCC"
    }
    property QtObject module: QtObject {
        property QtObject border: QtObject {
            property color colorNormal: "#000000"
            property color colorHover: "#AAAAAA"
            property color colorSelected: "#999999"
            property int width: 2
        }
        property color color: "#6666AA"
        property int radius: 5
    }
    property QtObject list: QtObject {
        property QtObject border: QtObject {
            property color color: "#000000"
            property int width: 2
        }
        property color highlight: "#999999"
        property color color: "#CCCCCC"
        property int radius: 5
    }
    property QtObject titleFont: QtObject {
        property bool bold: true
        property bool italic: false
        property int pointSize: 23 //25
    }
    property QtObject subTitleFont: QtObject {
        property bool bold: true
        property bool italic: false
        property int pointSize: 16 //18
    }
    property QtObject normalFont: QtObject {
        property bool bold: false
        property bool italic: false
        property int pointSize: 14 //16
    }
    property QtObject copyrightFont: QtObject {
        property bool bold: false
        property bool italic: false
        property int pointSize: 6 //8
    }
}
