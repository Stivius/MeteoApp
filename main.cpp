#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>

#include "bluetooth/model/ConnectionHandler.hpp"
#include "bluetooth/model/DeviceFinder.hpp"
#include "bluetooth/model/DeviceHandler.hpp"
#include "bluetooth/model/ChunkedDataParser.hpp"

#include "weather/model/CurrentWeatherModel.hpp"
#include "weather/model/ForecastWeatherModel.hpp"

#include "iconproviders/ApplicationTheme.hpp"
#include "iconproviders/BluetoothIconsProvider.hpp"
#include "iconproviders/WeatherIconsProvider.hpp"

#include "core/GlobalSettings.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QStringListModel locationListModel{QStringList{"Current", "Kharkiv", "Kiev", "London"}};
    ConnectionHandler connectionHandler;
    DeviceHandler deviceHandler( std::make_unique<ChunkedDataParser>() );
    DeviceFinder deviceFinder(&deviceHandler);

    CurrentWeatherModel::registerQmlType();
    ForecastWeatherModel::registerQmlType();
    qmlRegisterUncreatableType<DeviceHandler>("DeviceHandler", 1, 0, "AddressType", "Enum is not a type");
    qmlRegisterSingletonType(QUrl("qrc:/CommonSettings.qml"), "CommonSettings", 1, 0, "CommonSettings" );
    qmlRegisterSingletonType(QUrl("qrc:/ThemeController.qml"), "ThemeController", 1, 0, "ThemeController" );
    qmlRegisterSingletonType(QUrl("qrc:/FontSizes.qml"), "FontSizes", 1, 0, "FontSizes" );
    qmlRegisterSingletonType(QUrl("qrc:/bluetooth/ui/BluetoothWindowSettings.qml"), "BluetoothWindowSettings", 1, 0, "BluetoothWindowSettings" );
    qmlRegisterSingletonType(QUrl("qrc:/weather/ui/WeatherScreenSettings.qml"), "WeatherScreenSettings", 1, 0, "WeatherScreenSettings" );
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("connectionHandler", &connectionHandler);
    engine.rootContext()->setContextProperty("deviceFinder", &deviceFinder);
    engine.rootContext()->setContextProperty("deviceHandler", &deviceHandler);
    engine.rootContext()->setContextProperty("locationListModel", &locationListModel);
    engine.rootContext()->setContextProperty("appSettings", &GlobalSettings::get());

    ApplicationTheme::registerType();
    qmlRegisterType<BaseIconsProvider>();

    WeatherIconsProvider* weatherIconsProvider = new WeatherIconsProvider();
    engine.rootContext()->setContextProperty( "weatherIconsProvider", weatherIconsProvider );
    engine.addImageProvider( "weathericonsprovider", weatherIconsProvider );

    BluetoothIconsProvider* bluetoothIconsProvider = new BluetoothIconsProvider();
    engine.rootContext()->setContextProperty( "bluetoothIconsProvider", bluetoothIconsProvider );
    engine.addImageProvider( "bluetoothiconsprovider", bluetoothIconsProvider );


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
