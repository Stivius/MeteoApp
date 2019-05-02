#include "Resources.hpp"

#include "core/api/ApiConfig.hpp"

QString Resources::getApiService(WeatherInfo info)
{
    switch (info)
    {
        case WeatherInfo::Current: return ApiConfig::currentWeatherApi();
        case WeatherInfo::Hourly: return ApiConfig::hourlyForecstApi();
        case WeatherInfo::Daily: return ApiConfig::dailyForecstApi();
    }

    return QString{};
}

QString Resources::getTimeInterval(HistoricalWeatherMode mode)
{
    switch (mode)
    {
        case HistoricalWeatherMode::Day: return "1";
        case HistoricalWeatherMode::Week: return "6";
        case HistoricalWeatherMode::Month: return "24";
    }

    return QString{};
}

QUrl Resources::formRequestUrl(const QString& apiService, const std::map<QString, QString>& params)
{
    QUrl apiRequest{apiService};
    QUrlQuery query;

    for(auto [name, value] : params)
    {
        query.addQueryItem(name, value);
    }

    apiRequest.setQuery(query);

    return apiRequest;
}
