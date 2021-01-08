import QtQuick 2.9
import QtQuick.Controls 2.5
import QtCharts 2.3
import QtQuick.Layouts 1.12

import HistoricalWeatherModel 1.0
import CommonSettings 1.0
import FontSizes 1.0

Rectangle {
    anchors.fill: parent
    color: CommonSettings.backgroundColor

    ColumnLayout {
        spacing: CommonSettings.wHeight * 0.016

        Rectangle {
            Layout.preferredWidth: CommonSettings.wWidth
            Layout.preferredHeight: CommonSettings.wHeight / 3;

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
                     name: "Temperature"
                     axisX: axisX
                     axisY: axisY
                 }
            }
        }

        ColumnLayout {
            spacing: CommonSettings.wHeight * 0.008

            Text {
                font: CommonSettings.themeFont
                color: CommonSettings.fontColor
                text: qsTr("City: ") + model.city
            }

            Text {
                font: CommonSettings.themeFont
                color: CommonSettings.fontColor
                text: qsTr("Max Temperature: ") + model.minTemperature + " [" + model.minTemperatureDate + "]"
            }

            Text {
                font: CommonSettings.themeFont
                color: CommonSettings.fontColor
                text: qsTr("Min Temperature: ") + model.maxTemperature + " [" + model.maxTemperatureDate + "]"
            }
         }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            DatePicker {
                id: startDatePicker
            }

            DatePicker {
                id: endDatePicker
            }
        }

        Button {
            id: okButton
            Layout.alignment: Qt.AlignHCenter
            font: CommonSettings.themeFont
            text: "Ok"

            onClicked: {
                const _MS_PER_DAY = 1000 * 60 * 60 * 24;
                const daysDifference = Math.floor((endDatePicker.enteredDate - startDatePicker.enteredDate) / _MS_PER_DAY);
                if (daysDifference >= 35) {
                    errorDateDialog.open()
                }
                else {
                    model.request(startDatePicker.enteredDate, endDatePicker.enteredDate)
                }
            }
        }
    }

    InfoDialog {
        id: errorDateDialog
        title: "Date Error"
        message: "Date diff should be less than 35 days"
    }


    InfoDialog {
        id: emptyDataDialog
        title: "Empty Data"
        message: "Server gave no data for this period"
    }

    HistoricalWeatherModel {
        id: model

        onTemperatureDotsChanged: {
            axisX.max = temperatureDots.length
            axisY.min = minTemperature
            axisY.max = maxTemperature
            dotsSeries.clear()
            if (temperatureDots.length > 0) {
                for (var i = 0; i < temperatureDots.length; ++i) {
                    dotsSeries.append(i, dots[i])
                }
            }
            else {
                emptyDataDialog.open()
            }
        }
    }

}
