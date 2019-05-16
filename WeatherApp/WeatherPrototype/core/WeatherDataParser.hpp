#pragma once

#include <QByteArray>

template <typename WeatherData>
class WeatherDataParser
{
public:
    virtual ~WeatherDataParser() = default;
    virtual WeatherData parse(const QByteArray& data) = 0;

};
