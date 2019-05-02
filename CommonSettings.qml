pragma Singleton
import QtQuick 2.0

Item {
    property int wWidth
    property int wHeight

    function getPage(index)
    {
        switch(index)
        {
            case 0: return "weather/ui/WeatherScreen.qml"
            case 1: return "bluetooth/ui/SensorWeather.qml"
            case 2: return "historical/ui/HistoricalWeather.qml"
        }
    }
}
