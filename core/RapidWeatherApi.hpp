#pragma once

#include "WeatherBaseApi.hpp"

class RapidWeatherApi : public WeatherBaseApi
{
public:
    explicit RapidWeatherApi(const QString& apiKey, const QString& apiService, QObject* parent = nullptr);

protected:
    QNetworkRequest prepareNetworkRequest(const QUrl& url) override;

private:
    QString m_apiKey;

};

