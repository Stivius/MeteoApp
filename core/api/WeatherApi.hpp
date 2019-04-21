#pragma once

#include <QObject>

#include "core/api/ApiManager.hpp"
#include "core/api/WeatherInfo.hpp"
#include "core/model/WeatherData.hpp"

class WeatherApi : public QObject
{
    Q_OBJECT

signals:
    void currentWeatherReceived(const WeatherData& data);
    void forecastReceived(const WeatherDataCollection& collection);

public:
    explicit WeatherApi(QObject* parent = nullptr);

    // Hourly and Daily API are unstable and should not be used
    void requestCityWeather(const QString& city, WeatherInfo info = WeatherInfo::Current);

    // Hourly and Daily API are unstable and should not be used
    void requestWeatherByCoordinates(double latitude, double longitude, WeatherInfo info = WeatherInfo::Current);

private:
    void sendRequest(const QUrl& url);

private slots:
    void processResponse(const QJsonDocument& data);

private:
    ApiManager m_manager;

};
