#include "Config.hpp"

#include "Resources.hpp"

QSettings& Config::settings()
{
    static QSettings confSettings{Resources::Settings::File, QSettings::IniFormat};

    return confSettings;
}

QString Config::currentWeatherApi()
{
    return Config::settings().value(Resources::Settings::CurrentWeatherApiService).toString();
}

QString Config::hourlyForecstApi()
{
    return Config::settings().value(Resources::Settings::HourlyForecastApiService).toString();
}

QString Config::dailyForecstApi()
{
    return Config::settings().value(Resources::Settings::DailyForecastApiService).toString();
}

QString Config::historicalWeatherApi()
{
    return Config::settings().value(Resources::Settings::HistoricalWeatherApiService).toString();
}

QString Config::apiKey()
{
    return Config::settings().value(Resources::Settings::ApiKey).toString();
}

