#pragma once

#include <QObject>
#include <QDate>

#include "core/api/ApiManager.hpp"
#include "core/api/HistoricalWeatherMode.hpp"
#include "core/model/HistoricalWeatherWrappers.hpp"

class HistoricalWeatherApi : public QObject
{
    Q_OBJECT

signals:
    void weatherReceived(const HistoricalWeatherData& data);

public:
    explicit HistoricalWeatherApi(QObject* parent = nullptr);

    void requestWeather(const QString &city, HistoricalWeatherMode mode, const QDate& first, const QDate& last);

private:
    void sendRequest(const QUrl& url);

private slots:
    void processResponse(const QJsonDocument& data);
    void error(const QString& error);

private:
    ApiManager m_manager;

};
