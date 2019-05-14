#pragma once

#include <QDate>
#include <QObject>
#include <QNetworkAccessManager>

#include "core/WeatherBaseApi.hpp"

class HistoricalWeatherApi : public QObject
{
    Q_OBJECT

signals:
    void responseReceived(const QByteArray& data);
    void error(const QString& error);

public:
    explicit HistoricalWeatherApi(QObject* parent = nullptr);

    void requestWeather(const QString &city, const QDate& first, const QDate& last);

private:
    void sendRequest(const QUrl& url);

private slots:
    void requestFinished();
    void sslErrors(const QList<QSslError>& errors);

private:
    QNetworkAccessManager m_networkAccessManager;
};
