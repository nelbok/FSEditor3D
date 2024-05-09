import QtQuick
import QtQuick.Controls.Basic

import LHEditor

TextField {
    color: LHEStyle.foreground.normal
    placeholderTextColor: LHEStyle.foreground.placeholder
    palette.base: (enabled) ? LHEStyle.textfield.color : LHEStyle.textfield.disabled // Background color
    palette.mid: LHEStyle.textfield.border.normal // Border color
    palette.highlight: LHEStyle.textfield.border.selected // Border color
    font.bold: LHEStyle.normalFont.bold
    font.italic: LHEStyle.normalFont.italic
    font.pointSize: LHEStyle.normalFont.pointSize
}
