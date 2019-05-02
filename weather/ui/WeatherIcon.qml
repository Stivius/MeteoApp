import QtQuick 2.9

import ApplicationTheme 1.0

Image {
    property string weatherIcon

    id: img
    cache: false
    asynchronous: true
    source: getWeatherIcon( weatherIcon )
    smooth: true
    Connections
    {
        target: weatherIconsProvider
        onThemeChanged:
        {
            img.source = ""
            img.source = getWeatherIcon(container.weatherIcon);
        }
    }

    function getWeatherIcon( requestedIcon )
    {
        switch (requestedIcon) {
        case "01d":
        case "01n":
            return "image://weathericonsprovider/weather-sunny"
        case "02d":
        case "02n":
            return "image://weathericonsprovider/weather-sunny-very-few-clouds"
        case "03d":
        case "03n":
            return "image://weathericonsprovider/weather-few-clouds"
        case "04d":
        case "04n":
            return "image://weathericonsprovider/weather-overcast"
        case "09d":
        case "09n":
            return "image://weathericonsprovider/weather-showers"
        case "10d":
        case "10n":
            return "image://weathericonsprovider/weather-showers"
        case "11d":
        case "11n":
            return "image://weathericonsprovider/weather-thundershower"
        case "13d":
        case "13n":
            return "image://weathericonsprovider/weather-snow"
        case "50d":
        case "50n":
            return "image://weathericonsprovider/weather-fog"
        default:
            return "image://weathericonsprovider/weather-unknown"
        }
    }
}

