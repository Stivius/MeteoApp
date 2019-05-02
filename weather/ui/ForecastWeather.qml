import QtQuick 2.9

import ForecastWeatherModel 1.0

Item {
    property int iconWidth
    property int iconHeight

    Row {
        id: iconRow
        spacing: 6

        width: parent.width
        height: parent.height

        Repeater {
            model: ForecastWeatherModel { }

            delegate: ForecastItem {
                width: iconWidth
                height: iconHeight

                dayOfWeek: model.dayOfWeek
                minTemperature: model.minTemperature
                maxTemperature: model.maxTemperature
                icon: model.weatherIcon
            }
        }
    }
}


