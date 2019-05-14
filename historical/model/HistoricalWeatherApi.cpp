#include "HistoricalWeatherApi.hpp"
#include "core/ApiConfig.hpp"

#include <QNetworkReply>
#include <QUrlQuery>

HistoricalWeatherApi::HistoricalWeatherApi(QObject* parent) :
    QObject(parent)
{
}

static QString getTimePeriod(const QDate& first, const QDate& last)
{
    qint64 tp = first.daysTo(last);
    switch(tp)
    {
        case 0: return "24";  // Day mode
        case 6: return "3";   // Week mode
        default: return "1";  // Month mode
    }
}

void HistoricalWeatherApi::requestWeather(const QString &city, const QDate& first, const QDate& last)
{
    // Assume that the data is correct
    Q_ASSERT(first.isValid());
    Q_ASSERT(last.isValid());
    Q_ASSERT(last >= first);

    QString dateFormat = "yyyy-MM-dd";
    QUrl apiRequest{ApiConfig::historicalWeatherApi()};
    QUrlQuery query;

    query.addQueryItem("q", city);
    query.addQueryItem("format", "json");
    query.addQueryItem("date", first.toString(dateFormat));
    query.addQueryItem("enddate", first.toString(dateFormat));
    query.addQueryItem("tp", getTimePeriod(first, last));
    query.addQueryItem("key", ApiConfig::historicalApiKey());

    apiRequest.setQuery(query);


    sendRequest(apiRequest);
}

void HistoricalWeatherApi::sendRequest(const QUrl& url)
{
    auto reply = m_networkAccessManager.get(QNetworkRequest{url});

    connect(reply, &QNetworkReply::finished, this, &HistoricalWeatherApi::requestFinished);
    connect(reply, &QNetworkReply::sslErrors, this, &HistoricalWeatherApi::sslErrors);
}

void HistoricalWeatherApi::requestFinished()
{
    auto reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error())
    {
        emit error(reply->errorString());
    }
    else
    {
        emit responseReceived(reply->readAll());
    }

    reply->deleteLater();
}

void HistoricalWeatherApi::sslErrors(const QList<QSslError>& errors)
{
    QStringList errorList;

    for(const QSslError& error: errors)
    {
        errorList.append(error.errorString());
    }

    emit error(errorList.join('\n'));
}
