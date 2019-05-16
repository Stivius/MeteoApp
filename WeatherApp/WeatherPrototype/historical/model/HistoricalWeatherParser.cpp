#include "HistoricalWeatherParser.hpp"

#include <QJsonDocument>
#include <QJsonObject>

HistoricalWeatherData HistoricalWeatherParser::parse(const QByteArray& data)
{
    HistoricalWeatherData weather;
    QJsonDocument json = QJsonDocument::fromJson(data);

    auto requestInfo = json["data"]["request"].toArray().first().toObject();
    weather.city = requestInfo["query"].toString();

    HistoricalWeatherDayCollection days;
    auto weatherInfo = json["data"]["weather"].toArray();
    for(const auto dayInfo : weatherInfo)
    {
        HistoricalWeatherDay day = parseDay(dayInfo);
        days.push_back(day);
    }

    weather.days = days;
    return weather;
}

HistoricalWeatherDay HistoricalWeatherParser::parseDay(const QJsonValueRef dayInfo)
{
    HistoricalWeatherDay day;
    day.maxTemperature = dayInfo.toObject()["maxtempC"].toString().toInt();
    day.minTemperature = dayInfo.toObject()["mintempC"].toString().toInt();
    day.date = QDate::fromString(dayInfo.toObject()["date"].toString(), "yyyy-MM-dd");

    HistoricalWeatherUnitCollection hourly;
    auto hours = dayInfo.toObject()["hourly"].toArray();
    for(const auto unitInfo : hours)
    {
        HistoricalWeatherUnit unit = parseUnit(unitInfo);
        hourly.push_back(unit);
    }
    day.timeIntervals = hourly;
    return day;
}

HistoricalWeatherUnit HistoricalWeatherParser::parseUnit(const QJsonValueRef unitInfo)
{
    HistoricalWeatherUnit unit;
    unit.condition = unitInfo.toObject()["weatherDesc"].toArray().first().toObject()["value"].toString();
    unit.temperature = unitInfo.toObject()["tempC"].toString().toInt();
    unit.humidity = unitInfo.toObject()["humidity"].toString().toInt();
    unit.cloudcover = unitInfo.toObject()["cloudcover"].toString().toInt();
    unit.pressure = unitInfo.toObject()["pressure"].toString().toInt();
    return unit;
}
