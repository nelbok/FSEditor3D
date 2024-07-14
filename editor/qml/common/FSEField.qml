import QtQuick
import QtQuick.Controls.Basic

import editor

TextField {
    color: MyStyles.current.foreground.normal
    placeholderTextColor: MyStyles.current.foreground.alternative
    palette.base: (enabled) ? MyStyles.current.textfield.normal : MyStyles.current.textfield.disabled // Background color
    palette.mid: MyStyles.current.textfield.border.normal // Border color
    palette.highlight: MyStyles.current.textfield.border.selected // Border color
    font.bold: MyStyles.current.normalFont.bold
    font.italic: MyStyles.current.normalFont.italic
    font.pointSize: MyStyles.current.normalFont.pointSize
}
