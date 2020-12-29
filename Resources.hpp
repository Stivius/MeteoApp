#pragma once

#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <map>


namespace Resources
{
    namespace Settings
    {
        const QString File = ":/settings.conf";

        const QString CurrentWeatherApiService = "CurrentWeatherApiService";
        const QString ForecastWeatherApiService = "ForecastWeatherApiService";
        const QString HistoricalWeatherApiService = "HistoricalWeatherApiService";
        const QString CurrentWeatherApiKey = "CurrentWeatherApiKey";
        const QString ForecastWeatherApiKey = "ForecastWeatherApiKey";
        const QString HistoricalWeatherApiKey = "HistoricalWeatherApiKey";
    }
}
