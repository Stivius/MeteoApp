import QtQuick 2.0

Item {
    id: container

    property string weatherIcon

    Image {
        id: img
        cache: false
        asynchronous: true
        source: {
            switch (weatherIcon) {
            case "01d":
            case "01n":
                 "image://weathericonsprovider/weather-sunny"
                break;
            case "02d":
            case "02n":
                "image://weathericonsprovider/weather-sunny-very-few-clouds"
                break;
            case "03d":
            case "03n":
                "image://weathericonsprovider/weather-few-clouds"
                break;
            case "04d":
            case "04n":
                "image://weathericonsprovider/weather-overcast"
                break;
            case "09d":
            case "09n":
                "image://weathericonsprovider/weather-showers"
                break;
            case "10d":
            case "10n":
                "image://weathericonsprovider/weather-showers"
                break;
            case "11d":
            case "11n":
                "image://weathericonsprovider/weather-thundershower"
                break;
            case "13d":
            case "13n":
                "image://weathericonsprovider/weather-snow"
                break;
            case "50d":
            case "50n":
                "image://weathericonsprovider/weather-fog"
                break;
            default:
                "image://weathericonsprovider/weather-unknown"
                break;
            }
        }
        smooth: true
        anchors.fill: parent
    }
}
