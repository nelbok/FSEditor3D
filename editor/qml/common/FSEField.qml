import QtQuick
import QtQuick.Controls.Basic

import editor

TextField {
    color: MyManager.style.foreground.normal
    placeholderTextColor: MyManager.style.foreground.alternative
    palette.base: (enabled) ? MyManager.style.textfield.color : MyManager.style.textfield.disabled // Background color
    palette.mid: MyManager.style.textfield.border.normal // Border color
    palette.highlight: MyManager.style.textfield.border.selected // Border color
    font.bold: MyManager.style.normalFont.bold
    font.italic: MyManager.style.normalFont.italic
    font.pointSize: MyManager.style.normalFont.pointSize
}
