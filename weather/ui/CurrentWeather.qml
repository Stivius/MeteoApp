import QtQuick 2.0
import QtQuick.Controls 2.5

import CurrentWeather 1.0

Item {

    Column {
        anchors.centerIn: parent

        BigForecastIcon {
            id: forecastIcon
            width: 500//parent.width -12
            height: 600//2 * (parent.height - 25 - 12) / 2

            weatherIcon: (model.icon)
            topText: (model.minTemperature + "°/" + model.maxTemperature) + "°"
            bottomText: (model.description)
        }

        Row {
            id: iconRow
            spacing: 6

            width: 500
            height: 200

            property real iconWidth: iconRow.width / 4 - 10
            property real iconHeight: iconRow.height

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
            y: 500
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
