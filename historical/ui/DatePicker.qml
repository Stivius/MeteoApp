import QtQuick 2.0
import QtQuick.Controls 2.5
import CommonSettings 1.0

Row {
    spacing: 10

    property date enteredDate: new Date(year.value, month.currentIndex + 1, day.value)

    SpinBox {
        id: day
        font: CommonSettings.themeFont
        width: CommonSettings.wWidth * .25
        from: 1
        to: 31
        value:  new Date().getDay()
        editable: true
    }

    ComboBox {
        id: month
        font: CommonSettings.themeFont
        width: CommonSettings.wWidth * .4
        model: ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    }

    SpinBox {
        id: year
        font: CommonSettings.themeFont
        width: CommonSettings.wWidth * .3
        from: 2008
        to: new Date().getFullYear()
        value: new Date().getFullYear()
        editable: true
    }
}

