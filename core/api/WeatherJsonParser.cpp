#include "WeatherJsonParser.hpp"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

WeatherJsonParser::WeatherJsonParser(QObject *parent) :
    QObject(parent)
{
}

WeatherDataCollection WeatherJsonParser::parseFromJson(const QJsonDocument& data)
{
    auto root = data.object();

    if(root.contains("list"))
    {
        WeatherDataCollection collection;

        auto array = root["list"].toArray();
        for(const QJsonValue& data : array)
        {
            collection.push_back(parseJsonObject(data.toObject()));
        }

        return collection;
    }
    else
    {
        return {parseJsonObject(root)};
    }
}

WeatherData WeatherJsonParser::parseJsonObject(const QJsonObject& data)
{
    WeatherData weather;

    auto weatherInfo = data["weather"].toArray().first().toObject();

    QDateTime date = QDateTime::fromMSecsSinceEpoch(toMSSinceEpoch(data["dt"]));
    weather.dayOfTheWeek = date.date().toString(QStringLiteral("ddd"));
    weather.city = data["name"].toString();
    weather.condition = weatherInfo["main"].toString();
    weather.description = weatherInfo["description"].toString();
    weather.weatherIcon = weatherInfo["icon"].toString();

    weather.temperature = data["main"]["temp"].toDouble();
    weather.temperatureMin = data["main"]["temp_min"].toDouble();
    weather.temperatureMax = data["main"]["temp_max"].toDouble();

    if(!weather.temperatureMin)
    {
        weather.temperatureMin = data["temp"]["min"].toDouble();
        weather.temperatureMax = data["temp"]["max"].toDouble();
    }

    weather.pressure = data["main"]["pressure"].toInt();
    weather.humidity = data["main"]["humidity"].toInt();

    weather.windSpeed = data["windpw"]["speed"].toInt();
    weather.windDirection = data["wind"]["deg"].toInt();
    weather.cloudiness = data["clouds"]["all"].toInt();

    return weather;
}

qint64 WeatherJsonParser::toMSSinceEpoch(QJsonValue&& value) const
{
    return static_cast<qint64>(value.toDouble()*1000);
}
