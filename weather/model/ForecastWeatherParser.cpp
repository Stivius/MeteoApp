#include "ForecastWeatherParser.hpp"

#include <iostream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

static qint64 toMSSinceEpoch(const QJsonValue& value)
{
    return static_cast<qint64>(value.toDouble() * 1000);
}

WeatherDataCollection ForecastWeatherParser::parse(const QByteArray& data)
{
    QJsonParseError error;
    auto json = QJsonDocument::fromJson(data, &error);

    if(error.error != QJsonParseError::NoError)
    {
       qCritical() << error.errorString();
       return WeatherDataCollection{};
    }

    auto root = json.object();
    if(root.contains("list"))
    {
        WeatherDataCollection collection;

        auto array = root["list"].toArray();
        for(QJsonValueRef value : array)
        {
            collection.push_back(parseJsonObject(value.toObject()));
        }

        return collection;
    }
    else
    {
        return {parseJsonObject(root)};
    }
}

WeatherApiData ForecastWeatherParser::parseJsonObject(const QJsonObject& data)
{
    WeatherApiData weather;
    auto weatherInfo = data["weather"].toArray().first().toObject();

    QDateTime date = QDateTime::fromMSecsSinceEpoch(toMSSinceEpoch(data["dt"]));

    weather.dayOfTheWeek = date.date().toString(QStringLiteral("ddd"));    
    weather.condition = weatherInfo["main"].toString();
    weather.description = weatherInfo["description"].toString();
    weather.weatherIcon = weatherInfo["icon"].toString();

    weather.temperatureMin = static_cast<int>(data["temp"]["min"].toDouble());
    weather.temperatureMax = static_cast<int>(data["temp"]["max"].toDouble());

    return weather;
}
