pragma Singleton

import QtQuick 2.9
import CommonSettings 1.0

Item {

    property real bigIconWidth: CommonSettings.wWidth
    property real bigIconHeight: CommonSettings.wHeight* .65

    property real  rowWidth: CommonSettings.wWidth
    property real  rowHeight: CommonSettings.wHeight * .25

    property real  rowIconWidth: rowWidth / 4 - 10
    property real  rowIconHeight: rowHeight

}
