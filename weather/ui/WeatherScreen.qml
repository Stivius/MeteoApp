import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

import WeatherScreenSettings 1.0
import ApplicationTheme 1.0
import ThemeController 1.0
import CommonSettings 1.0

Rectangle {
    anchors.fill: parent

    color: CommonSettings.backgroundColor

    Switch {
        id:switchItem;
        anchors.right: parent.right
        anchors.top: parent.top
        Component.onCompleted: {
            switchItem.checked = ThemeController.currentAppTheme !== AppThemeEnum.Light;
        }
        onClicked: {
            var newTheme = switchItem.checked? AppThemeEnum.Dark : AppThemeEnum.Light
            ThemeController.changeTheme( newTheme )
            console.log("Clicked, checked = ", newTheme )
        }
    }

    ColumnLayout {
        anchors.centerIn: parent

        CurrentWeather {
            Layout.alignment: Qt.AlignHCenter
            width: WeatherScreenSettings.currentWeatherWidth
            height: WeatherScreenSettings.currentWeatherHeight
        }

        ForecastWeather{
            Layout.topMargin: WeatherScreenSettings.forecastHeight * 0.45
            Layout.fillWidth: true;
            Layout.alignment: Qt.AlignHCenter
            width: WeatherScreenSettings.forecastWidth
            height: WeatherScreenSettings.forecastHeight

            iconWidth: WeatherScreenSettings.forecastIconWidth
            iconHeight: WeatherScreenSettings.forecastIconHeight
        }

        LocationList {
            Layout.topMargin: WeatherScreenSettings.locationListHeight * 0.1
            Layout.alignment: Qt.AlignHCenter
            width: WeatherScreenSettings.locationListWidth
            height: WeatherScreenSettings.locationListHeight
        }
    }
}
