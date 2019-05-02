#include "HistoricalWeatherApi.hpp"
#include "HistoricalWeatherJsonParser.hpp"

#include "Resources.hpp"
#include "ApiConfig.hpp"

HistoricalWeatherApi::HistoricalWeatherApi(QObject* parent) :
    QObject(parent)
{
}

void HistoricalWeatherApi::requestWeather(const QString &city, HistoricalWeatherMode mode, const QDate& first, const QDate& last)
{
    Q_ASSERT(first.isValid());
    Q_ASSERT(last.isValid());

    auto service = ApiConfig::historicalWeatherApi();
    std::map<QString, QString> params;
    QString dateFormat = "yyyy-MM-dd";

    params["q"] = city;
    params["format"] = "json";
    params["date"] = first.toString(dateFormat);
    params["enddate"] = last.toString(dateFormat);
    params["tp"] = Resources::getTimeInterval(mode);
    params["key"] = ApiConfig::historicalApiKey();

    sendRequest(Resources::formRequestUrl(service, params));
}

void HistoricalWeatherApi::sendRequest(const QUrl& url)
{
    auto request = QSharedPointer<ApiRequest>::create(url);

    connect(request.get(), &ApiRequest::received, this, &HistoricalWeatherApi::processResponse);
    connect(request.get(), &ApiRequest::error, this, &HistoricalWeatherApi::error);

    m_manager.sendRequest(request);
}

void HistoricalWeatherApi::processResponse(const QJsonDocument& data)
{
    HistoricalWeatherJsonParser parser;
    auto result = parser.parseFromJson(data);
    emit weatherReceived(result);
}

void HistoricalWeatherApi::error(const QString& error)
{
    qDebug() << error;
}
