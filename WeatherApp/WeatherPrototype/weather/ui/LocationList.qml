import QtQuick.Controls 2.5
import QtQml 2.9
import QtQuick 2.9

import CommonSettings 1.0
import FontSizes 1.0

Rectangle
{
    id: current
    anchors.leftMargin: CommonSettings.wWidth *0.02
    anchors.rightMargin: CommonSettings.wWidth *0.02

    color: Qt.darker(CommonSettings.backgroundColor, 1.2)
    radius: CommonSettings.wWidth *0.01

    Component
    {
        id:pathViewDelegate
        Rectangle
        {
            antialiasing: true
            height: current.height;
            width: current.width - previousCityButton.width - nextCityButton.width;
            color: "transparent"
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: display;
                font.pixelSize: FontSizes.largeFontSize;
                font.family: CommonSettings.themeFont
                color: CommonSettings.fontColor
             }
        }
    }
    PathView {
        id:citiesView
        anchors.fill: parent
        model:locationListModel

        delegate: pathViewDelegate
        preferredHighlightBegin: 0.5;
        preferredHighlightEnd: 0.5;

        highlightRangeMode: PathView.StrictlyEnforceRange
        pathItemCount:1
        maximumFlickVelocity:1000
        path: Path {
            startX: 0;
            startY:current.height/2;
            PathLine {
                x:current.width ; y: current.height/2
            }
        }
        onCurrentIndexChanged:
        {
            appSettings.location = locationListModel.data(locationListModel.index(this.currentIndex ,0 ) );
        }
    }

    SwitchSityButton
    {
        id: previousCityButton
        displayedText:"V"
        rotationAngle: 90
        onClicked:
        {
            citiesView.decrementCurrentIndex();
        }
    }
    SwitchSityButton
    {
        id: nextCityButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        displayedText:"V"
        rotationAngle: 270
        onClicked:
        {
            citiesView.incrementCurrentIndex();
        }
    }
}
