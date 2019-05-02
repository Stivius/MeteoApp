#pragma once

#include <QString>
#include <QDateTime>
#include <vector>

struct WeatherApiData
{
    QString city;
    QString condition;
    QString dayOfTheWeek;
    QString description;
    QString weatherIcon;
    int temperature;
    int temperatureMin;
    int temperatureMax;
    int pressure;
    int humidity;
};

using WeatherDataCollection = std::vector<WeatherApiData>;
