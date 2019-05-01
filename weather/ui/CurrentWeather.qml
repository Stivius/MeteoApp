import QtQuick 2.0
import QtQuick.Controls 2.5

import CurrentWeather 1.0
import CommonSettings 1.0

import WeatherWindowSettings 1.0
import ApplicationTheme 1.0
import ThemeController 1.0

Rectangle{
    anchors.fill: parent

    color: CommonSettings.backgroundColor

    Switch {
        id:switchItem;
        anchors.right: parent.right
        anchors.top: parent.top
        Component.onCompleted:
        {
            switchItem.checked = ThemeController.currentAppTheme!= AppThemeEnum.Light;
        }
        onClicked:
        {
            var newTheme = switchItem.checked? AppThemeEnum.Dark : AppThemeEnum.Light
            ThemeController.changeTheme( newTheme )
            console.log("Clicked, checked = ", newTheme )
        }
       }
    Column {
        anchors.centerIn: parent
        BigForecastIcon {
            id: forecastIcon
            width: WeatherWindowSettings.bigIconWidth
            height: WeatherWindowSettings.bigIconHeight

            weatherIcon: (model.icon)
            topText: (model.minTemperature + "°/" + model.maxTemperature) + "°"
            bottomText: (model.description)
        }

        Row {
            id: iconRow
            spacing: 6

            width: WeatherWindowSettings.rowWidth
            height: WeatherWindowSettings.rowHeight

            property real iconWidth: WeatherWindowSettings.rowIconWidth
            property real iconHeight: WeatherWindowSettings.rowIconHeight

            ForecastIcon {
                id: forecast0
                width: iconRow.iconWidth
                height: iconRow.iconHeight

                topText: model.forecast[1].dayOfWeek
                bottomText: model.forecast[1].minTemperature + "°/" + model.forecast[0].maxTemperature + "°"
                weatherIcon: model.forecast[1].weatherIcon
            }
            ForecastIcon {
                id: forecast1
                width: iconRow.iconWidth
                height: iconRow.iconHeight

                topText: model.forecast[2].dayOfWeek
                bottomText: model.forecast[2].minTemperature + "°/" + model.forecast[1].maxTemperature + "°"
                weatherIcon: model.forecast[2].weatherIcon
            }
            ForecastIcon {
                id: forecast2
                width: iconRow.iconWidth
                height: iconRow.iconHeight

                topText: model.forecast[3].dayOfWeek
                bottomText: model.forecast[3].minTemperature + "°/" + model.forecast[2].maxTemperature + "°"
                weatherIcon: model.forecast[3].weatherIcon
            }
            ForecastIcon {
                id: forecast3
                width: iconRow.iconWidth
                height: iconRow.iconHeight

                topText: model.forecast[4].dayOfWeek
                bottomText: model.forecast[4].minTemperature + "°/" + model.forecast[3].maxTemperature + "°"
                weatherIcon: model.forecast[4].weatherIcon
            }
        }

        ComboBox {
            id: cityList
            model: ["Current", "London", "Kharkiv", "Kiev"]

            onCurrentTextChanged: {
                if(cityList.currentText == "Current") {
                    model.requestCurrentGeoWeather();
                }
                else {
                    model.requestCityWeather(cityList.currentText);
                    model.requestCityForecast(cityList.currentText);
                }
            }
        }
    }

    CurrentWeather {
        id: model
    }
}
