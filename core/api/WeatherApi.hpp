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

    void requestCityWeather(const QString& city);
    void requestCityForecast(const QString& city);
    void requestWeatherByCoordinates(double latitude, double longitude, WeatherInfo info = WeatherInfo::Current);

private:
    void sendRequest(const QUrl& url);

private slots:
    void processResponse(const QJsonDocument& data);
    void error(const QString& error);

private:
    ApiManager m_manager;

};
