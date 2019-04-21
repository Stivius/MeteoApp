#pragma once

#include <QString>
#include <vector>

struct WeatherData
{
    QString city;
    QString condition;
    QString description;
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
