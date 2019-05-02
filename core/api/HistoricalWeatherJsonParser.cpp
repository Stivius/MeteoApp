#include "HistoricalWeatherJsonParser.hpp"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

HistoricalWeatherJsonParser::HistoricalWeatherJsonParser(QObject *parent) :
    QObject(parent)
{
}

HistoricalWeatherData HistoricalWeatherJsonParser::parseFromJson(const QJsonDocument& data)
{
    HistoricalWeatherData weather;

    auto requestInfo = data["data"]["request"].toArray().first().toObject();
    weather.city = requestInfo["query"].toString();

    HistoricalWeatherDayCollection days;
    auto weatherInfo = data["data"]["weather"].toArray();
    for(const auto dayInfo : weatherInfo)
    {
        HistoricalWeatherDay day;
        day.maxTemperature = dayInfo.toObject()["maxtempC"].toString().toInt();
        day.minTemperature = dayInfo.toObject()["mintempC"].toString().toInt();
        day.date = QDate::fromString(dayInfo.toObject()["date"].toString(), "yyyy-MM-dd");

        HistoricalWeatherUnitCollection hourly;
        auto hours = dayInfo.toObject()["hourly"].toArray();
        for(const auto unitInfo : hours)
        {
            HistoricalWeatherUnit unit;
            unit.condition = unitInfo.toObject()["weatherDesc"].toArray().first().toObject()["value"].toString();
            unit.temperature = unitInfo.toObject()["tempC"].toString().toInt();
            unit.humidity = unitInfo.toObject()["humidity"].toString().toInt();
            unit.cloudcover = unitInfo.toObject()["cloudcover"].toString().toInt();
            unit.pressure = unitInfo.toObject()["pressure"].toString().toInt();

            hourly.push_back(unit);
        }
        day.timeIntervals = hourly;
        days.push_back(day);
    }

    weather.days = days;
    return weather;
}
