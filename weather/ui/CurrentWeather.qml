import QtQuick 2.0
import QtQuick.Controls 2.5

import CurrentWeather 1.0

Item {

    Column {
        anchors.centerIn: parent

        spacing: 10

        Text {
            text: qsTr("City: ") + model.city
        }

        Text {
            text: qsTr("Condition: ") + model.condition
        }

        Text {
            text: qsTr("Description: ") + model.description
        }

        Text {
            text: qsTr("Temperature: ") + model.temperature
        }

        Text {
            text: qsTr("Pressure: ") + model.pressure
        }

        Text {
            text: qsTr("Humdity: ") + model.humidity
        }

        ComboBox {
            id: cityList
            model: ["Current", "London", "Kharkiv", "Kiev"]

            onCurrentTextChanged: {
                if(cityList.currentText == "Current") {
                    model.requestCurrentGeoWeather();
                }
                else {
                    model.requestCityWeather(cityList.currentText)
                }
            }
        }
    }
    CurrentWeather {
        id: model
    }
}
