#pragma once

#include <QString>
#include <QDateTime>
#include <vector>

struct WeatherData
{
    QString city;
    QString condition;
    QString dayOfTheWeek;
    QString description;
    QString weatherIcon;
    double temperature;
    double temperatureMin;
    double temperatureMax;
    double pressure;
    int humidity;
    double windSpeed;
    int windDirection;
    int cloudiness;
};

using WeatherDataCollection = std::vector<WeatherData>;
