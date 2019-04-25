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
