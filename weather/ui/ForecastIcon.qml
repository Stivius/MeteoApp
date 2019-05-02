import QtQuick 2.0
import CommonSettings 1.0
import FontSizes 1.0
Item {
    id: top

    property string topText: "Mon"
    property string weatherIcon: "01d"
    property string bottomText: "22*/23*"

    Text { 
        id: dayText
        horizontalAlignment: Text.AlignHCenter
        width: top.width
        text: top.topText
        font.pointSize: FontSizes.smallTinyFontSize
        font.family: CommonSettings.themeFont
        color: CommonSettings.fontColor
        anchors.top: parent.top
        anchors.topMargin: top.height / 5 - dayText.paintedHeight
        anchors.horizontalCenter: parent.horizontalCenter
    }

    WeatherIcon {
        id: icon
        weatherIcon: top.weatherIcon

        property real side: {
            var iconHight = top.height * .6
            if (top.width < iconHight)
                top.width;
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
        width: top.width
        text: top.bottomText
        font.pointSize: FontSizes.smallTinyFontSize
        font.family: CommonSettings.themeFont
        color: CommonSettings.fontColor

        anchors.bottom: parent.bottom
        anchors.bottomMargin: top.height / 5 - tempText.paintedHeight
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
