#pragma once

#include <QSettings>

class ApiConfig
{
    Q_DISABLE_COPY(ApiConfig)

public:
    static QString currentWeatherApiService();
    static QString forecstWeatherApiService();
    static QString historicalWeatherApiService();

    static QString currentWeatherApiKey();
    static QString forecastWeatherApiKey();
    static QString historicalWeatherApiKey();

private:
    static QSettings& settings();

};
