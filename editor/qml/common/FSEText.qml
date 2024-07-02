import QtQuick

import editor

Text {
    horizontalAlignment: Text.AlignRight

    color: MyManager.style.foreground.normal
    font.bold: MyManager.style.normalFont.bold
    font.italic: MyManager.style.normalFont.italic
    font.pointSize: MyManager.style.normalFont.pointSize
}
