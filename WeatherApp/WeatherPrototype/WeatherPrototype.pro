QT += quick widgets positioning charts bluetooth
CONFIG += c++17

#QMAKE_CXXFLAGS += /std:c++17
#Uncomment for passing MSVC build
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
    bluetooth/model/DeviceFinder.cpp \
    bluetooth/model/DeviceHandler.cpp \
    bluetooth/model/DeviceInfo.cpp \
    bluetooth/model/ChunkedDataParser.cpp \
    iconproviders/WeatherIconsProvider.cpp \
    iconproviders/ResourcesIcons.cpp \
    iconproviders/BaseIconsProvider.cpp \
    iconproviders/BluetoothIconsProvider.cpp \
    main.cpp \
    core/ApiConfig.cpp \
    core/GeoPositioning.cpp \
    core/WeatherBaseApi.cpp \
    core/GlobalSettings.cpp \
    weather/model/CurrentWeatherApi.cpp \
    weather/model/CurrentWeatherModel.cpp \
    weather/model/CurrentWeatherParser.cpp \
    weather/model/ForecastWeatherApi.cpp \
    weather/model/ForecastWeatherModel.cpp \
    weather/model/ForecastWeatherParser.cpp \
    historical/model/HistoricalWeatherApi.cpp \
    historical/model/HistoricalWeatherParser.cpp \
    historical/model/HistoricalWeatherModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(android-openssl.pri)

HEADERS += \
    bluetooth/model/BluetoothBaseClass.hpp \
    bluetooth/model/ConnectionHandler.hpp \
    bluetooth/model/DeviceFinder.hpp \
    bluetooth/model/DeviceHandler.hpp \
    bluetooth/model/DeviceInfo.hpp \
    bluetooth/model/IReceivedDataParser.hpp \
    bluetooth/model/BluetoothModelResources.hpp\
    bluetooth/model/ChunkedDataParser.hpp\
    iconproviders/WeatherIconsProvider.hpp \
    iconproviders/ResourcesIcons.hpp \
    bluetooth/model/BadPacketException.hpp \
    iconproviders/ApplicationTheme.hpp \
    iconproviders/BaseIconsProvider.hpp \
    iconproviders/BluetoothIconsProvider.hpp \
    Resources.hpp \
    core/ApiConfig.hpp \
    core/GeoPositioning.hpp \
    core/WeatherModel.hpp \
    core/WeatherBaseApi.hpp \
    core/WeatherDataParser.hpp \
    core/GlobalSettings.hpp \
    weather/model/WeatherData.hpp \
    weather/model/CurrentWeatherApi.hpp \
    weather/model/CurrentWeatherModel.hpp \
    weather/model/CurrentWeatherParser.hpp \
    weather/model/ForecastWeatherApi.hpp \
    weather/model/ForecastWeatherModel.hpp \
    weather/model/ForecastWeatherParser.hpp \
    historical/model/HistoricalWeatherApi.hpp \
    historical/model/HistoricalWeatherData.hpp \
    historical/model/HistoricalWeatherParser.hpp \
    historical/model/HistoricalWeatherModel.hpp

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
