#include "QMLWeaterData.hpp"

AWeatherData::AWeatherData(QObject *parent) :
        QObject(parent)
{
}

AWeatherData::AWeatherData(const AWeatherData &other) :
        QObject(nullptr),
        m_dayOfWeek(other.m_dayOfWeek),
        m_weatherIcon(other.m_weatherIcon),
        m_weatherDescription(other.m_weatherDescription),
        m_maxTemperature(other.m_maxTemperature),
        m_minTemperature(other.m_minTemperature)
{
}

QString AWeatherData::dayOfWeek() const
{
    return m_dayOfWeek;
}

QString AWeatherData::city() const
{
    return m_city;
}

QString AWeatherData::weatherIcon() const
{
    return m_weatherIcon;
}

QString AWeatherData::weatherDescription() const
{
    return m_weatherDescription;
}

QString AWeatherData::condition() const
{
    return m_condition;
}

int AWeatherData::maxTemperature() const
{
    return m_maxTemperature;
}

int AWeatherData::minTemperature() const
{
    return m_minTemperature;
}

double AWeatherData::pressure() const
{
    return m_pressure;
}

int AWeatherData::humidity() const
{
    return m_humidity;
}

void AWeatherData::setDayOfWeek(const QString &value)
{
    m_dayOfWeek = value;
    emit dataChanged();
}

void AWeatherData::setCity(const QString &value)
{
    m_city = value;
    emit dataChanged();
}

void AWeatherData::setWeatherIcon(const QString &value)
{
    m_weatherIcon = value;
    emit dataChanged();
}

void AWeatherData::setWeatherDescription(const QString &value)
{
    m_weatherDescription = value;
    emit dataChanged();
}

void AWeatherData::setCondition(const QString &value)
{
    m_condition = value;
    emit dataChanged();
}

void AWeatherData::setMaxTemperature(int value)
{
    m_maxTemperature = value;
    emit dataChanged();
}

void AWeatherData::setMinTemperature(int value)
{
    m_minTemperature = value;
    emit dataChanged();
}

void AWeatherData::setPressure(double value)
{
    m_pressure = value;
    emit dataChanged();
}

void AWeatherData::setHumidity(int value)
{
    m_humidity = value;
    emit dataChanged();
}
