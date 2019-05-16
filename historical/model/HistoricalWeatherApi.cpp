#include "HistoricalWeatherApi.hpp"

#include "core/ApiConfig.hpp"

HistoricalWeatherApi::HistoricalWeatherApi(DateCallback callback, QObject* parent) :
    WeatherBaseApi(parent),
    m_dateDelegate{callback}
{
}

static QString getTimeInterval(const QDate& date, const QDate& enddate)
{
    qint64 interval = date.daysTo(enddate);
    switch(interval)
    {
        case 0: return "24";  // Day mode
        case 6: return "3";   // Week mode
        default: return "1";  // Month mode
    }
}

QUrl HistoricalWeatherApi::formRequest(const QString& city)
{
    auto [date, enddate] = m_dateDelegate();

    std::map<QString, QString> params = {
        {"q", city},
        {"format", "json"},
        {"date", date.toString(ms_dateFormat)},
        {"enddate", enddate.toString(ms_dateFormat)},
        {"tp", getTimeInterval(date, enddate)},
        {"key", ApiConfig::historicalApiKey()}
    };

    return formRequestUrl(ApiConfig::historicalWeatherApi(), params);
}

QUrl HistoricalWeatherApi::formRequest(double latitude, double longitude)
{
    auto [date, enddate] = m_dateDelegate();

    std::map<QString, QString> params = {
        {"q", QString("%1,%2").arg(QString::number(latitude), QString::number(longitude))},
        {"format", "json"},
        {"date", date.toString(ms_dateFormat)},
        {"enddate", enddate.toString(ms_dateFormat)},
        {"tp", getTimeInterval(date, enddate)},
        {"key", ApiConfig::historicalApiKey()}
    };

    return formRequestUrl(ApiConfig::historicalWeatherApi(), params);
}

const QString HistoricalWeatherApi::ms_dateFormat = "yyyy-MM-dd";
