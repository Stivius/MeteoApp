import QtQuick 2.9
import QtQuick.Controls 2.5

import CurrentWeatherModel 1.0
import FontSizes 1.0
import CommonSettings 1.0

Item {
    id: current

    property real smallSide: (current.width < current.height ? current.width : current.height)

    Text {
        text: model.temperature + "°"

        font.pointSize: FontSizes.largeFontSize
        font.family: CommonSettings.themeFont
        color: CommonSettings.fontColor

        anchors {
            top: current.top
            left: current.left
            topMargin: 5
            leftMargin: 5
        }
    }

    WeatherIcon {
        id: currentWeatherIcon
        weatherIcon: model.icon
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -15
        width: current.smallSide
        height: current.smallSide
    }

    Text {
        text: model.condition
        width: parent.width
        wrapMode: Text.WordWrap

        font.pointSize: FontSizes.mediumFontSize
        font.family: CommonSettings.themeFont
        color: CommonSettings.fontColor

        horizontalAlignment: Text.AlignRight
        anchors {
            top: currentWeatherIcon.bottom
            right: current.right
            rightMargin: 5
        }
    }

    CurrentWeatherModel {
        id: model
    }
}
