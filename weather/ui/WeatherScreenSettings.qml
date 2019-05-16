pragma Singleton
import QtQuick 2.9

import CommonSettings 1.0

Item {

    property real currentWeatherWidth: CommonSettings.wWidth
    property real currentWeatherHeight: CommonSettings.wHeight * .4

    property real forecastWidth: CommonSettings.wWidth
    property real forecastHeight: CommonSettings.wHeight * .25

    property real forecastIconWidth: forecastWidth / 4 - 10
    property real forecastIconHeight: forecastHeight

    property real locationListWidth: CommonSettings.wWidth
    property real locationListHeight: CommonSettings.wHeight * 0.1
}
