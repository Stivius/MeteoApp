#include "ForecastWeatherParser.hpp"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

ForecastWeatherParser::ForecastWeatherParser(QObject *parent) :
    QObject(parent)
{
}

WeatherDataCollection ForecastWeatherParser::parse(const QByteArray& data)
{
    auto json = QJsonDocument::fromJson(data);
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
    weather.city = data["name"].toString();
    weather.condition = weatherInfo["main"].toString();
    weather.description = weatherInfo["description"].toString();
    weather.weatherIcon = weatherInfo["icon"].toString();

    weather.temperature = data["main"]["temp"].toInt();
    weather.temperatureMin = data["main"]["temp_min"].toInt();
    weather.temperatureMax = data["main"]["temp_max"].toInt();

    weather.pressure = data["main"]["pressure"].toInt();
    weather.humidity = data["main"]["humidity"].toInt();

    return weather;
}

qint64 ForecastWeatherParser::toMSSinceEpoch(QJsonValue&& value) const
{
    return static_cast<qint64>(value.toDouble() * 1000);
}
