#pragma once

#include <QSettings>

class ApiConfig
{
    Q_DISABLE_COPY(ApiConfig)

public:
    static QString currentWeatherApi();
    static QString hourlyForecstApi();
    static QString dailyForecstApi();
    static QString historicalWeatherApi();

    static QString historicalApiKey();
    static QString apiKey();

private:
    static QSettings& settings();

};
