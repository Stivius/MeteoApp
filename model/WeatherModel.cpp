#include "WeatherModel.hpp"

WeatherModel::WeatherModel(QObject* parent) :
    QObject(parent), m_dataSource(new WeatherApi())
{
    connect(m_dataSource, &WeatherApi::currentWeatherReceived, this, &WeatherModel::updateModel);
    connect(&m_geoPositioning, &GeoPositioning::coordsUpdated, this, &WeatherModel::requestWeatherByCoords);
}

void WeatherModel::requestCityWeather(const QString& city)
{
    m_dataSource->requestCityWeather(city);
}

void WeatherModel::requestCurrentGeoWeather()
{
    m_geoPositioning.requestUpdates();
}

void WeatherModel::requestWeatherByCoords(double latitude, double longitude)
{
    m_dataSource->requestWeatherByCoordinates(latitude, longitude);
}

QString WeatherModel::city() const
{
    return m_city;
}

void WeatherModel::setCity(const QString& cityName)
{
    m_city = cityName;
    emit cityChanged(cityName);
}

QString WeatherModel::condition() const
{
    return m_condition;
}

void WeatherModel::setCondition(const QString& condition)
{
    m_condition = condition;
    emit conditionChanged(condition);
}

QString WeatherModel::description() const
{
    return m_description;
}

void WeatherModel::setDescription(const QString& description)
{
    m_description = description;
    emit descriptionChanged(description);
}

double WeatherModel::temperature() const
{
    return m_temperature;
}

void WeatherModel::setTemperature(double temperature)
{
    m_temperature = temperature;
    emit temperatureChanged(temperature);
}

double WeatherModel::pressure() const
{
    return m_pressure;
}

void WeatherModel::setPressure(double pressure)
{
    m_pressure = pressure;
    emit pressureChanged(pressure);
}

int WeatherModel::humidity() const
{
    return m_humidity;
}

void WeatherModel::setHumidity(int humidity)
{
    m_humidity = humidity;
    emit humdityChanged(humidity);
}

void WeatherModel::updateModel(const WeatherData& data)
{
    setCity(data.city);
    setCondition(data.condition);
    setDescription(data.description);
    setTemperature(data.temperature);
    setPressure(data.pressure);
    setHumidity(data.humidity);
}
