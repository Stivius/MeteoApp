#include "ApiConfig.hpp"

#include "Resources.hpp"

QSettings& ApiConfig::settings()
{
    static QSettings confSettings{Resources::Settings::File, QSettings::IniFormat};

    return confSettings;
}

QString ApiConfig::currentWeatherApi()
{
    return ApiConfig::settings().value(Resources::Settings::CurrentWeatherApiService).toString();
}

QString ApiConfig::hourlyForecstApi()
{
    return ApiConfig::settings().value(Resources::Settings::HourlyForecastApiService).toString();
}

QString ApiConfig::dailyForecstApi()
{
    return ApiConfig::settings().value(Resources::Settings::DailyForecastApiService).toString();
}

QString ApiConfig::historicalWeatherApi()
{
    return ApiConfig::settings().value(Resources::Settings::HistoricalWeatherApiService).toString();
}

QString ApiConfig::historicalApiKey()
{
    return ApiConfig::settings().value(Resources::Settings::HistoricalApiKey).toString();
}

QString ApiConfig::apiKey()
{
    return ApiConfig::settings().value(Resources::Settings::ApiKey).toString();
}

