import QtQuick.Controls 2.5
import QtQml 2.9

ComboBox {
    textRole: "display"
    model: locationListModel

    onCurrentTextChanged: {
        appSettings.location = currentText;
    }
}

