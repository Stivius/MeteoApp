import QtQuick 2.9
import QtQml.StateMachine 1.15 as DSM

import ForecastWeatherModel 1.0
import FontSizes 1.0
import CommonSettings 1.0

Item {
    property int iconWidth
    property int iconHeight

    Row {
        id: iconRow
        spacing: 6

        width: parent.width
        height: parent.height

        Repeater {
            model: ForecastWeatherModel {
                id: forecastModel
            }

            delegate: ForecastItem {
                width: iconWidth
                height: iconHeight

                dayOfWeek: model.dayOfWeek
                minTemperature: model.minTemperature
                maxTemperature: model.maxTemperature
                icon: model.weatherIcon
            }
        }
    }

    Text {
        id: loadingText
        text: "Loading..."
        width: parent.width
        wrapMode: Text.WordWrap

        font.pointSize: FontSizes.bigFontSize
        font.family: CommonSettings.themeFont
        color: CommonSettings.fontColor

        horizontalAlignment: Text.AlignHCenter
    }

    DSM.StateMachine {
       id: stateMachine
       initialState: loadingState
       running: true
       DSM.State {
           id: loadingState

           DSM.SignalTransition {
               targetState: loadedState
               signal: forecastModel.dataUpdated
           }
           onEntered: {
               iconRow.visible = false
               loadingText.visible = true
           }
       }
       DSM.State {
           id: loadedState

           onEntered: {
               iconRow.visible = true
               loadingText.visible = false
           }
       }
   }
}


