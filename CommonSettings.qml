pragma Singleton
import QtQuick 2.9

Item {
    property int wWidth
    property int wHeight

    function getPage(index)
    {
        switch(index)
        {
            case 0: return "bluetooth/ui/SensorWeather.qml"
            case 1: return "weather/ui/WeatherScreen.qml"
            case 2: return "historical/ui/HistoricalWeather.qml"
        }
    }

     FontLoader {
        id: applicationFont;
        source: "CornDemo-Regular.ttf"
    }

    readonly property color darkBackgroundColor: "#503247"
    readonly property color darkDigitsColor: "#7a90c2"

    readonly property color lightBackgroundColor: "#538e8c"
    readonly property color lightDigitsColor: "#aaf0f0"

    property color backgroundColor: darkBackgroundColor
    property color digitsColor: darkDigitsColor

    property color fontColor: darkDigitsColor

    property string themeFont: applicationFont.name
}
