pragma Singleton
import QtQuick 2.9

import CommonSettings 1.0

Item {
    // Colors
    readonly property color backgroundColor: CommonSettings.backgroundColor
    readonly property color buttonColor: Qt.darker(CommonSettings.backgroundColor, 1.5)
    readonly property color buttonPressedColor: Qt.darker(CommonSettings.backgroundColor, 1.5)
    readonly property color disabledButtonColor: "#555555"
    readonly property color viewColor: Qt.darker(CommonSettings.backgroundColor, 1.3)
    readonly property color delegate1Color: Qt.darker(viewColor, 1.2)
    readonly property color delegate2Color: Qt.lighter(viewColor, 1.2)
    readonly property color textColor: Qt.lighter(CommonSettings.fontColor, 1.2 )
    readonly property color messageCenterTextColor: "#ffffff"
    readonly property color textDarkColor:  Qt.darker( CommonSettings.fontColor , 1.8 )
    readonly property color disabledTextColor: "#777777"
    readonly property color errorColor: "#ba3f62"
    readonly property color infoColor: "#3fba62"

    // Some other values
    property real fieldHeight: CommonSettings.wHeight * 0.08
    property real fieldMargin: fieldHeight * 0.5
    property real buttonHeight: CommonSettings.wHeight * 0.08
    property real buttonRadius: buttonHeight * 0.1

    // Some help functions
    function widthForHeight(h, ss)
    {
        return h/ss.height * ss.width;
    }

    function heightForWidth(w, ss)
    {
        return w/ss.width * ss.height;
    }

}
