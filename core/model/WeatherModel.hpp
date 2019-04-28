#pragma once

#include <QObject>

#include "core/api/WeatherApi.hpp"
#include "core/model/GeoPositioning.hpp"
#include "core/model/QMLWeatherData.hpp"
#include "core/model/PrivateWeatherAccessor.hpp"

class WeatherModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString city READ city NOTIFY cityChanged)
    Q_PROPERTY(QString condition READ condition NOTIFY conditionChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(double maxTemperature READ maxTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(double minTemperature READ minTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(double pressure READ pressure NOTIFY pressureChanged)
    Q_PROPERTY(int humidity READ humidity NOTIFY humdityChanged)
    Q_PROPERTY(QQmlListProperty<AWeatherData> forecast
               READ forecast
               NOTIFY forecastChanged)

signals:
    void cityChanged(const QString& city);
    void conditionChanged(const QString& condition);
    void descriptionChanged(const QString& desription);
    void iconChanged(const QString& icon);
    void temperatureChanged(double temperature);
    void pressureChanged(double pressure);
    void humdityChanged(int humidity);
    void forecastChanged(QQmlListProperty<AWeatherData> forecast);

public:
    WeatherModel(QObject* parent = nullptr);

    Q_INVOKABLE void requestCityWeather(const QString& city);
    Q_INVOKABLE void requestCityForecast(const QString& city);
    Q_INVOKABLE void requestCurrentGeoWeather();

    QString city() const;
    QString condition() const;
    QString description() const;
    QString icon() const;
    double maxTemperature() const;
    double minTemperature() const;
    double pressure() const;
    int humidity() const;
    QQmlListProperty<AWeatherData> forecast() const;



private slots:
    void requestWeatherByCoords(double latitude, double longitude);

private:
    void updateModel(const WeatherData& data);
    void updateForecast(const WeatherDataCollection& data);

    void setCity(const QString& city);
    void setCondition(const QString& condition);
    void setDescription(const QString& description);
    void setIcon(const QString& icon);
    void setMaxTemperature(int temperature);
    void setMinTemperature(int temperature);
    void setPressure(double pressure);
    void setHumidity(int value);

private:
    GeoPositioning m_geoPositioning;
    WeatherApi* m_dataSource = nullptr;
    std::unique_ptr<PrivateWeatherAccessor> m_WeatherAccessor;
};
