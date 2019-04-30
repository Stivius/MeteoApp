import QtQuick 2.0

Item {
    id: container

    property string weatherIcon

    Image {
        id: img
        source: {
            switch (weatherIcon) {
            case "01d":
            case "01n":
                 "qrc:/icons/weather-sunny.png"
                break;
            case "02d":
            case "02n":
                "qrc:/icons/weather-sunny-very-few-clouds.png"
                break;
            case "03d":
            case "03n":
                "qrc:/icons/weather-few-clouds.png"
                break;
            case "04d":
            case "04n":
                "qrc:/icons/weather-overcast.png"
                break;
            case "09d":
            case "09n":
                "qrc:/icons/weather-showers.png"
                break;
            case "10d":
            case "10n":
                "qrc:/icons/weather-showers.png"
                break;
            case "11d":
            case "11n":
                "qrc:/icons/weather-thundershower.png"
                break;
            case "13d":
            case "13n":
                "qrc:/icons/weather-snow.png"
                break;
            case "50d":
            case "50n":
                "qrc:/icons/weather-fog.png"
                break;
            default:
                "qrc:/icons/weather-unknown.png"
                break;
            }
        }
        smooth: true
        anchors.fill: parent
    }
}
