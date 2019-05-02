import QtQuick 2.0

Item {
    id: current

    property string dayOfWeek: "Mon"
    property string icon: "01d"
    property int minTemperature: 22
    property int maxTemperature: 23

    Text { 
        id: dayText
        horizontalAlignment: Text.AlignHCenter
        width: current.width
        text: current.dayOfWeek

        anchors.top: parent.top
        anchors.topMargin: current.height / 5 - dayText.paintedHeight
        anchors.horizontalCenter: parent.horizontalCenter
    }

    WeatherIcon {
        id: icon
        weatherIcon: current.icon

        property real side: {
            var iconHight = current.height * .6
            if (current.width < iconHight)
                current.width;
            else
                iconHight;
        }

        width: icon.side
        height: icon.side

        anchors.centerIn: parent
    }

    Text {
        id: tempText
        horizontalAlignment: Text.AlignHCenter
        width: current.width
        text: current.minTemperature + "°/" + current.maxTemperature + "°"

        anchors.bottom: parent.bottom
        anchors.bottomMargin: current.height / 5 - tempText.paintedHeight
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
