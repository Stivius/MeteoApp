#include <QQmlApplicationEngine>
#include <QApplication>

#include "WeatherModel.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    qmlRegisterType<WeatherModel>("CurrentWeather", 1, 0, "CurrentWeather");
    qmlRegisterSingletonType(QUrl("qrc:/Resources.qml"), "Resources", 1, 0, "Resources" );

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
