#include "Resources.hpp"
#include "Config.hpp"

QString Resources::getCollection(WeatherInfo info)
{
    switch (info)
    {
        case WeatherInfo::Current: return Config::currentWeatherApi();
        case WeatherInfo::Hourly: return Config::hourlyForecstApi();
        case WeatherInfo::Daily: return Config::hourlyForecstApi();
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
