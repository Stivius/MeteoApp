import QtQuick 2.0
import QtQuick.Controls 2.5
import CurrentWeatherModel 1.0
import FontSizes 1.0

Item {
    id: current

    property real smallSide: (current.width < current.height ? current.width : current.height)

    Text {
        text: model.temperature + "°"
        font.pointSize: FontSizes.largeFontSize
        anchors {
            top: current.top
            left: current.left
            topMargin: 5
            leftMargin: 5
        }
    }

    WeatherIcon {
        weatherIcon: model.icon
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -15
        width: current.smallSide
        height: current.smallSide
    }

    Text {
        text: model.condition
        font.pointSize: FontSizes.mediumFontSize
        wrapMode: Text.WordWrap
        width: parent.width
        horizontalAlignment: Text.AlignRight
        anchors {
            bottom: current.bottom
            right: current.right
            rightMargin: 5
        }
    }

    CurrentWeatherModel {
        id: model
    }
}
