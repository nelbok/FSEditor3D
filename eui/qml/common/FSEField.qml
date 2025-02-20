import QtQuick
import QtQuick.Controls.Basic

import eui

TextField {
    color: MyStyles.style.foreground.normal
    placeholderTextColor: MyStyles.style.foreground.alternative
    palette.base: (enabled) ? MyStyles.style.textfield.normal : MyStyles.style.textfield.disabled // Background color
    palette.mid: MyStyles.style.textfield.border.normal // Border color
    palette.highlight: MyStyles.style.textfield.border.selected // Border color
    font.bold: MyStyles.style.normalFont.bold
    font.italic: MyStyles.style.normalFont.italic
    font.pointSize: MyStyles.style.normalFont.pointSize
}
