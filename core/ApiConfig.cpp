#include "ApiConfig.hpp"

#include "Resources.hpp"

QSettings& ApiConfig::settings()
{
    static QSettings confSettings{Resources::Settings::File, QSettings::IniFormat};

    return confSettings;
}

QString ApiConfig::currentWeatherApiService()
{
    return ApiConfig::settings().value(Resources::Settings::CurrentWeatherApiService).toString();
}

QString ApiConfig::forecstWeatherApiService()
{
    return ApiConfig::settings().value(Resources::Settings::ForecastWeatherApiService).toString();
}

QString ApiConfig::historicalWeatherApiService()
{
    return ApiConfig::settings().value(Resources::Settings::HistoricalWeatherApiService).toString();
}

QString ApiConfig::currentWeatherApiKey()
{
    return ApiConfig::settings().value(Resources::Settings::CurrentWeatherApiKey).toString();
}

QString ApiConfig::forecastWeatherApiKey()
{
    return ApiConfig::settings().value(Resources::Settings::ForecastWeatherApiKey).toString();
}

QString ApiConfig::historicalWeatherApiKey()
{
    return ApiConfig::settings().value(Resources::Settings::HistoricalWeatherApiKey).toString();
}
