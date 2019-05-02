import QtQuick 2.0
import WeatherScreenSettings 1.0

Item {

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
