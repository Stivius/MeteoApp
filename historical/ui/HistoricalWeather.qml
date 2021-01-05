import QtQuick 2.9
import QtQuick.Controls 2.5
import QtCharts 2.3

import HistoricalWeatherModel 1.0
import CommonSettings 1.0
import FontSizes 1.0

Rectangle {
    anchors.fill: parent
    color: CommonSettings.backgroundColor


    Rectangle {
        width: parent.width - 10
        height: parent.height / 3;

        ChartView {
            id: chartView
            anchors.fill: parent
            antialiasing: true
            theme: ChartView.ChartThemeDark
            animationOptions: ChartView.NoAnimation
            backgroundColor: CommonSettings.backgroundColor

            ValueAxis {
                 id: axisX
                 min: 0
                 max: 10
                 labelsVisible: false
                 gridVisible: false
             }

             ValueAxis {
                 id: axisY
                 min: -0.5
                 max: 1.5
             }

             LineSeries {
                 id: dotsSeries
                 name: "temperature"
                 axisX: axisX
                 axisY: axisY
             }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        Column {
            spacing: 10

            Text {
                font: CommonSettings.themeFont
                color: CommonSettings.fontColor
                text: qsTr("City: ") + model.city
            }

            Text {
                font: CommonSettings.themeFont
                color: CommonSettings.fontColor
                text: qsTr("MaxTemperature: ") + model.minTemperature + " [" + model.minTemperatureDate + "]"
            }

            Text {
                font: CommonSettings.themeFont
                color: CommonSettings.fontColor
                text: qsTr("MinTemperature: ") + model.maxTemperature + " [" + model.maxTemperatureDate + "]"
            }
         }

        DatePicker {
            id: startDatePicker
        }

        DatePicker {
            id: endDatePicker
        }


        Column {
            spacing: 10

            Button {
                id: okButton
                font: CommonSettings.themeFont
                text: "Ok"

                onClicked: {
                    model.request(startDatePicker.enteredDate, endDatePicker.enteredDate)
                }
            }

        }

    }

    HistoricalWeatherModel {
        id: model

        onTemperatureDotsChanged: {
            axisX.max = temperatureDots.length
            axisY.min = minTemperature
            axisY.max = maxTemperature
            dotsSeries.clear()
            for (var i = 0; i < temperatureDots.length; ++i) {
                dotsSeries.append(i, dots[i])
            }
        }
    }

}
