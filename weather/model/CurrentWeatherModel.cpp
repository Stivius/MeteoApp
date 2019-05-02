#include "CurrentWeatherModel.hpp"

#include "weather/model/CurrentWeatherParser.hpp"
#include "weather/model/CurrentWeatherApi.hpp"

#include <QQmlEngine>

CurrentWeatherModel::CurrentWeatherModel(QObject* parent) :
    WeatherModel(std::make_unique<CurrentWeatherApi>(),
                 std::make_unique<CurrentWeatherParser>(),
                 parent)
{
}

void CurrentWeatherModel::registerQmlType()
{
    qmlRegisterType<CurrentWeatherModel>("CurrentWeatherModel", 1, 0, "CurrentWeatherModel");
}

void CurrentWeatherModel::updateModel(const WeatherDataCollection& data)
{
    auto&& weatherData = data.front();

    setCondition(weatherData.condition);
    setTemperature(weatherData.temperature);
    setIcon(weatherData.weatherIcon);
}

QString CurrentWeatherModel::condition() const
{
    return m_condition;
}

void CurrentWeatherModel::setCondition(const QString& condition)
{
    m_condition = condition;
    emit conditionChanged(condition);
}

QString CurrentWeatherModel::icon() const
{
    return m_icon;
}

void CurrentWeatherModel::setIcon(const QString &icon)
{
    m_icon = icon;
    emit iconChanged(icon);
}

int CurrentWeatherModel::temperature() const
{
    return m_temperature;
}

void CurrentWeatherModel::setTemperature(int temperature)
{
    m_temperature = temperature;
    emit temperatureChanged(temperature);
}
