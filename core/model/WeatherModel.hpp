#pragma once

#include <QObject>

#include "core/api/WeatherApi.hpp"
#include "core/model/GeoPositioning.hpp"

class WeatherModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString city READ city NOTIFY cityChanged)
    Q_PROPERTY(QString condition READ condition NOTIFY conditionChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(double pressure READ pressure NOTIFY pressureChanged)
    Q_PROPERTY(int humidity READ humidity NOTIFY humdityChanged)

signals:
    void cityChanged(const QString& city);
    void conditionChanged(const QString& condition);
    void descriptionChanged(const QString& desription);
    void temperatureChanged(double temperature);
    void pressureChanged(double pressure);
    void humdityChanged(int humidity);

public:
    WeatherModel(QObject* parent = nullptr);

    Q_INVOKABLE void requestCityWeather(const QString& city);
    Q_INVOKABLE void requestCurrentGeoWeather();

    QString city() const;
    QString condition() const;
    QString description() const;
    double temperature() const;
    double pressure() const;
    int humidity() const;

private slots:
    void requestWeatherByCoords(double latitude, double longitude);

private:
    void updateModel(const WeatherData& data);

    void setCity(const QString& city);
    void setCondition(const QString& condition);
    void setDescription(const QString& description);
    void setTemperature(double temperature);
    void setPressure(double pressure);
    void setHumidity(int value);

private:
    GeoPositioning m_geoPositioning;
    WeatherApi* m_dataSource = nullptr;

    QString m_city;
    QString m_condition;
    QString m_description;

    double m_temperature;
    double m_pressure;
    int m_humidity;
};
