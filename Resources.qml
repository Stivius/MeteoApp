pragma Singleton
import QtQuick 2.0

Item {
    readonly property int windowWidth: 640
    readonly property int windowHeight: 480

    function getPage(index)
    {
        switch(index)
        {
            case 0: return "CurrentWeather.qml"
            case 1: return "SensorWeather.qml"
            case 2: return "HistoricalWeather.qml"
        }
    }
}
