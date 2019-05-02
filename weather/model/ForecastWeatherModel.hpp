#pragma once

#include "core/WeatherModel.hpp"

class ForecastWeatherModel : public WeatherModel
{
    Q_OBJECT
    Q_PROPERTY(QVariantList forecast READ getForecast NOTIFY forecastChanged)

signals:
    void forecastChanged(const QVariantList& forecast);

public:
    ForecastWeatherModel(QObject* parent = nullptr);

    static void registerQmlType();
    QVariantList getForecast() const;

protected:
    void updateModel(const WeatherDataCollection& data) override;

private:
    void setForecast(const QVariantList& forecast);

private:
    QVariantList m_forecast;

};

