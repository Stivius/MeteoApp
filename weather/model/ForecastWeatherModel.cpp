#include "ForecastWeatherModel.hpp"

#include "weather/model/ForecastWeatherApi.hpp"
#include "weather/model/ForecastWeatherParser.hpp"
#include "weather/model/QmlWeatherData.hpp"

#include <QQmlEngine>

ForecastWeatherModel::ForecastWeatherModel(QObject* parent) :
    WeatherModel(std::make_unique<ForecastWeatherApi>(),
                 std::make_unique<ForecastWeatherParser>(),
                 parent)
{
}

void ForecastWeatherModel::registerQmlType()
{
    qmlRegisterType<ForecastWeatherModel>("ForecastWeatherModel", 1, 0, "ForecastWeatherModel");
}

QVariantList ForecastWeatherModel::getForecast() const
{
    return m_forecast;
}

void ForecastWeatherModel::setForecast(const QVariantList& forecast)
{
    m_forecast = forecast;
    emit forecastChanged(forecast);
}

void ForecastWeatherModel::updateModel(const WeatherDataCollection& data)
{
    QList<QVariant> forecast;
    for(auto&& value : data)
    {
        QmlWeatherData weatherData;
        weatherData.setDayOfWeek(value.dayOfTheWeek);
        weatherData.setMaxTemperature(value.temperatureMax);
        weatherData.setMinTemperature(value.temperatureMin);
        weatherData.setWeatherDescription(value.description);
        weatherData.setCondition(value.condition);
        weatherData.setWeatherIcon(value.weatherIcon);
        forecast.append(QVariant::fromValue(weatherData));
    }

    setForecast(forecast);
}
