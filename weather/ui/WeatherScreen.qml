import QtQuick 2.0
import QtQuick.Controls 2.5

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

    Column {
        anchors.centerIn: parent

        CurrentWeather {
            width: WeatherScreenSettings.currentWeatherWidth
            height: WeatherScreenSettings.currentWeatherHeight
        }

        ForecastWeather{
            width: WeatherScreenSettings.forecastWidth
            height: WeatherScreenSettings.forecastHeight

            iconWidth: WeatherScreenSettings.forecastIconWidth
            iconHeight: WeatherScreenSettings.forecastIconHeight
        }

        LocationList {
            y: 500
        }
    }
}
