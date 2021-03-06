#include "CurrentWeatherParser.hpp"

#include <iostream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

static qint64 toMSSinceEpoch(const QJsonValue&& value)
{
    return static_cast<qint64>(value.toDouble() * 1000);
}

WeatherApiData CurrentWeatherParser::parse(const QByteArray& data)
{
    QJsonParseError error;
    auto json = QJsonDocument::fromJson(data, &error);

    if(error.error != QJsonParseError::NoError)
    {
       qCritical() << error.errorString();
       return WeatherApiData{};
    }

    WeatherApiData weather;
    auto weatherInfo = json["weather"].toArray().first();

    QDateTime date = QDateTime::fromMSecsSinceEpoch(toMSSinceEpoch(json["dt"]));

    weather.dayOfTheWeek = date.date().toString(QStringLiteral("ddd"));
    weather.condition = weatherInfo["main"].toString();
    weather.description = weatherInfo["description"].toString();
    weather.weatherIcon = weatherInfo["icon"].toString();

    weather.temperature = static_cast<int>(json["main"]["temp"].toDouble());
    weather.temperatureMin = static_cast<int>(json["main"]["temp_min"].toDouble());
    weather.temperatureMax = static_cast<int>(json["main"]["temp_max"].toDouble());

    weather.pressure = json["main"]["pressure"].toInt();
    weather.humidity = json["main"]["humidity"].toInt();

    return weather;
}
