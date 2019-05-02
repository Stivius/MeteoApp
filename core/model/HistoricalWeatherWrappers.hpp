/**
* Structures defined in this file are only suitable for storing historical weather data.
* They are not compatible with WeatherData and WeatherModel.
*/

#pragma once

#include <QString>
#include <QDate>
#include <vector>

struct HistoricalWeatherUnit
{
    QString condition;
    int temperature;
    int humidity;
    int pressure;
    int cloudcover;
};

using HistoricalWeatherUnitCollection = std::vector<HistoricalWeatherUnit>;

struct HistoricalWeatherDay
{
    QDate date;
    int maxTemperature;
    int minTemperature;
    HistoricalWeatherUnitCollection timeIntervals;
};

using HistoricalWeatherDayCollection = std::vector<HistoricalWeatherDay>;

struct HistoricalWeatherData
{
    QString city;
    HistoricalWeatherDayCollection days;
};
