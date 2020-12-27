#include "ForecastWeatherParser.hpp"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

constexpr int DaysNeeded = 4;

static qint64 toMSSinceEpoch(QJsonValue&& value)
{
    return static_cast<qint64>(value.toDouble() * 1000);
}

WeatherDataCollection ForecastWeatherParser::parse(const QByteArray& data)
{
    auto json = QJsonDocument::fromJson(data);
    auto root = json.object();

    if(root.contains("list"))
    {
        WeatherDataCollection collection;

        auto array = root["list"].toArray();

        int k = 0;
        for(QJsonValueRef value : array)
        {
            auto data = value.toObject();

            if(data["dt_txt"].toString().right(8) == "12:00:00")
            {
                collection.push_back(parseJsonObject(value.toObject()));
                ++k;
            }

            if(k == DaysNeeded)
                break;
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

    weather.temperatureMin = static_cast<int>(data["main"]["temp_min"].toDouble());
    weather.temperatureMax = static_cast<int>(data["main"]["temp_max"].toDouble());

    return weather;
}
