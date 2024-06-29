import QtQuick
import QtQuick.Controls.Basic

import editor

TextField {
    color: FSEStyle.foreground.normal
    placeholderTextColor: FSEStyle.foreground.placeholder
    palette.base: (enabled) ? FSEStyle.textfield.color : FSEStyle.textfield.disabled // Background color
    palette.mid: FSEStyle.textfield.border.normal // Border color
    palette.highlight: FSEStyle.textfield.border.selected // Border color
    font.bold: FSEStyle.normalFont.bold
    font.italic: FSEStyle.normalFont.italic
    font.pointSize: FSEStyle.normalFont.pointSize
}
