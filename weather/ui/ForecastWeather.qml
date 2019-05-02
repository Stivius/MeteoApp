import QtQuick 2.0
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
            model: 4

            ForecastItem {
                width: iconWidth
                height: iconHeight

                dayOfWeek: model.forecast[index].dayOfWeek
                minTemperature: model.forecast[index].minTemperature
                maxTemperature: model.forecast[index].maxTemperature
                icon: model.forecast[index].weatherIcon
            }
        }
    }

    ForecastWeatherModel {
        id: model
    }
}


