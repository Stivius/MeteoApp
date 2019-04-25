QT += quick widgets positioning charts bluetooth
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bluetooth/model/BluetoothBaseClass.cpp \
    bluetooth/model/ConnectionHandler.cpp \
    bluetooth/model/CustomFormatDataParser.cpp \
    bluetooth/model/DeviceFinder.cpp \
    bluetooth/model/DeviceHandler.cpp \
    bluetooth/model/DeviceInfo.cpp \
    bluetooth/model/JsonFormatDataParser.cpp \
    bluetooth/model/receiveddataparser.cpp \
    core/api/ApiManager.cpp \
    core/api/ApiRequest.cpp \
    core/api/WeatherApi.cpp \
    core/api/WeatherJsonParser.cpp \
    core/api/ApiConfig.cpp \
    core/model/GeoPositioning.cpp \
    core/model/QMLWeatherData.cpp \
    core/model/WeatherModel.cpp \
    main.cpp \
    Resources.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#copydata.commands = $(COPY_DIR) $$PWD/settings.conf $$OUT_PWD
#first.depends = $(first) copydata
#export(first.depends)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first copydata

HEADERS += \
    bluetooth/model/BluetoothBaseClass.hpp \
    bluetooth/model/ConnectionHandler.hpp \
    bluetooth/model/CustomFormatDataParser.hpp \
    bluetooth/model/DeviceFinder.hpp \
    bluetooth/model/DeviceHandler.hpp \
    bluetooth/model/DeviceInfo.hpp \
    bluetooth/model/IReceivedDataParser.hpp \
    bluetooth/model/JsonFormatDataParser.hpp \
    bluetooth/model/simulator-config.hpp \
    core/api/ApiManager.hpp \
    core/api/ApiRequest.hpp \
    core/api/WeatherApi.hpp \
    core/api/WeatherInfo.hpp \
    core/api/WeatherJsonParser.hpp \
    core/api/ApiConfig.hpp \
    core/model/GeoPositioning.hpp \
    core/model/QMLWeaterData.hpp \
    core/model/WeatherData.hpp \
    core/model/WeatherModel.hpp \
    Resources.hpp \
    core/model/privateweatheraccessor.hpp

DISTFILES += \
    icons/README.txt \
    icons/qt_attribution.json \
    icons/weather-few-clouds.png \
    icons/weather-fog.png \
    icons/weather-haze.png \
    icons/weather-icy.png \
    icons/weather-overcast.png \
    icons/weather-showers.png \
    icons/weather-sleet.png \
    icons/weather-snow.png \
    icons/weather-storm.png \
    icons/weather-sunny-very-few-clouds.png \
    icons/weather-sunny.png \
    icons/weather-thundershower.png
