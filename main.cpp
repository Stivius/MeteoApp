#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>

#include "core/model/WeatherModel.hpp"
#include "bluetooth/model/ConnectionHandler.hpp"
#include "bluetooth/model/DeviceFinder.hpp"
#include "bluetooth/model/DeviceHandler.hpp"
#include "bluetooth/model/CustomFormatDataParser.hpp"
#include "bluetooth/model/JsonFormatDataParser.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    ConnectionHandler connectionHandler;
    DeviceHandler deviceHandler( std::make_unique<JsonFormatDataParser>() );
    DeviceFinder deviceFinder(&deviceHandler);

    qmlRegisterUncreatableType<DeviceHandler>("DeviceHandler", 1, 0, "AddressType", "Enum is not a type");
    qmlRegisterType<WeatherModel>("CurrentWeather", 1, 0, "CurrentWeather");
    qmlRegisterSingletonType(QUrl("qrc:/CommonSettings.qml"), "CommonSettings", 1, 0, "CommonSettings" );
    qmlRegisterSingletonType(QUrl("qrc:/bluetooth/ui/BluetoothWindowSettings.qml"), "BluetoothWindowSettings", 1, 0, "BluetoothWindowSettings" );

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("connectionHandler", &connectionHandler);
    engine.rootContext()->setContextProperty("deviceFinder", &deviceFinder);
    engine.rootContext()->setContextProperty("deviceHandler", &deviceHandler);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
