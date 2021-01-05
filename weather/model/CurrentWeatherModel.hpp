#pragma once

#include "core/WeatherGeoModel.hpp"
#include "weather/model/WeatherData.hpp"

class CurrentWeatherModel : public WeatherGeoModel<WeatherApiData>
{
    Q_OBJECT

    Q_PROPERTY(QString condition READ condition NOTIFY conditionChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(int temperature READ temperature NOTIFY temperatureChanged)

signals:
    void conditionChanged(const QString& condition);
    void iconChanged(const QString& icon);
    void temperatureChanged(int temperature);

public:
    CurrentWeatherModel(QObject* parent = nullptr);

    static void registerQmlType();

    QString condition() const;
    QString icon() const;
    int temperature() const;

protected:
    void updateModel(const WeatherApiData& data) override;

private:
    void setCondition(const QString& condition);
    void setIcon(const QString& icon);
    void setTemperature(int temperature);

private:
    QString m_condition;
    QString m_icon;
    int m_temperature;

};

