pragma Singleton
import QtQuick 2.9

import CommonSettings 1.0

Item {
    // Font sizes
    property real microFontSize: hugeFontSize * 0.2
    property real tinyFontSize: hugeFontSize * 0.4
    property real smallTinyFontSize: hugeFontSize * 0.5
    property real smallFontSize: hugeFontSize * 0.6
    property real mediumFontSize: hugeFontSize * 0.7
    property real bigFontSize: hugeFontSize * 0.8
    property real largeFontSize: hugeFontSize * 0.9
    property real hugeFontSize: (CommonSettings.wWidth + CommonSettings.wHeight) * 0.03
    property real giganticFontSize: (CommonSettings.wWidth + CommonSettings.wHeight) * 0.04
}
