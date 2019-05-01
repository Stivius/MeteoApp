import QtQuick 2.0
import ApplicationTheme 1.0

Item {
    id: container

    property string weatherIcon
    Image {
        id: img
        cache: false
        asynchronous: true
        source: getWeatherIcon( weatherIcon )
        smooth: true
        anchors.fill: parent
        Connections
        {
            target: weatherIconsProvider
            onThemeChanged:
            {
                img.source = ""
                img.source = getWeatherIcon(container.weatherIcon);
            }
        }
    }

    function getWeatherIcon( requestedIcon )
    {
        switch (requestedIcon) {
        case "01d":
        case "01n":
             return "image://weathericonsprovider/weather-sunny"
            break;
        case "02d":
        case "02n":
            return "image://weathericonsprovider/weather-sunny-very-few-clouds"
            break;
        case "03d":
        case "03n":
            return "image://weathericonsprovider/weather-few-clouds"
            break;
        case "04d":
        case "04n":
            return "image://weathericonsprovider/weather-overcast"
            break;
        case "09d":
        case "09n":
            return "image://weathericonsprovider/weather-showers"
            break;
        case "10d":
        case "10n":
            return "image://weathericonsprovider/weather-showers"
            break;
        case "11d":
        case "11n":
            return "image://weathericonsprovider/weather-thundershower"
            break;
        case "13d":
        case "13n":
            return "image://weathericonsprovider/weather-snow"
            break;
        case "50d":
        case "50n":
            return "image://weathericonsprovider/weather-fog"
            break;
        default:
            return "image://weathericonsprovider/weather-unknown"
            break;
        }
    }
}

