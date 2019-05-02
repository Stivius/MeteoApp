import QtQuick 2.0
import QtQuick.Controls 2.5
import QtCharts 2.3

import HistoricalWeather 1.0
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
        }
    }

    function updateChart() {
        chartSource.update(chartView, model.temperatureDots, model.minTemperature, model.maxTemperature);
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
                text: qsTr("MinTemperature: ") + model.minTemperature + " [" + model.minTemperatureDate + "]"
            }
         }

        Row {
            spacing: 10

            ComboBox {
                id: dayList
                font: CommonSettings.themeFont
                width: CommonSettings.wWidth * .15
                model: ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"]
            }

            ComboBox {
                id: monthList
                font: CommonSettings.themeFont
                width: CommonSettings.wWidth * .4
                model: ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
            }

            ComboBox {
                id: yearList
                font: CommonSettings.themeFont
                width: CommonSettings.wWidth * .25
                model: ["2008", "2009", "2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017", "2018", "2019"]
            }

        }

        Column {
            spacing: 10

            Button {
                id: okButt
                font: CommonSettings.themeFont
                text: "Ok"

                onClicked: model.requestWeather(dayList.currentText, monthList.currentIndex + 1, yearList.currentText)
            }

        }

    }

    HistoricalWeather {
        id: model
    }

}
