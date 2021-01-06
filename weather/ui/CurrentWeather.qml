import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQml.StateMachine 1.15 as DSM

import CurrentWeatherModel 1.0
import FontSizes 1.0
import CommonSettings 1.0

Item {
    id: current

    property real smallSide: (current.width < current.height ? current.width : current.height)

    Text {
        text: loadedState.active ? model.temperature + "°" : ""

        font.pointSize: FontSizes.largeFontSize
        font.family: CommonSettings.themeFont
        color: CommonSettings.fontColor

        anchors {
            top: current.top
            left: current.left
            topMargin: 5
            leftMargin: 5
        }
    }

    WeatherIcon {
        id: currentWeatherIcon
        weatherIcon: loadedState.active ? model.icon : ""
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -15
        width: current.smallSide
        height: current.smallSide
    }

    Text {
        text: loadedState.active ? model.condition : ""
        width: parent.width
        wrapMode: Text.WordWrap

        font.pointSize: FontSizes.mediumFontSize
        font.family: CommonSettings.themeFont
        color: CommonSettings.fontColor

        horizontalAlignment: Text.AlignRight
        anchors {
            top: currentWeatherIcon.bottom
            right: current.right
            rightMargin: 5
        }
    }

    DSM.StateMachine {
       id: stateMachine
       initialState: loadingState
       running: true
       DSM.State {
           id: loadingState

           DSM.SignalTransition {
               targetState: loadedState
               signal: model.dataUpdated
           }
       }
       DSM.State {
           id: loadedState
       }
   }

    CurrentWeatherModel {
        id: model
    }
}
