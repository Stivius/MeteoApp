#pragma once

#include <QSettings>

class Config
{
    Q_DISABLE_COPY(Config)

public:
    static QString currentWeatherApi();
    static QString hourlyForecstApi();
    static QString dailyForecstApi();
    static QString historicalWeatherApi();

    static QString apiKey();

private:
    static QSettings& settings();

private:

};
