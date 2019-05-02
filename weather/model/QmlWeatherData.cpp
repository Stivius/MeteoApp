#include "QmlWeatherData.hpp"

QmlWeatherData::QmlWeatherData(QObject *parent) :
        QObject(parent)
{
}

QmlWeatherData::QmlWeatherData(const QmlWeatherData &other) :
        QObject(nullptr),
        m_dayOfWeek(other.m_dayOfWeek),
        m_weatherIcon(other.m_weatherIcon),
        m_weatherDescription(other.m_weatherDescription),
        m_maxTemperature(other.m_maxTemperature),
        m_minTemperature(other.m_minTemperature)
{
}

QString QmlWeatherData::dayOfWeek() const
{
    return m_dayOfWeek;
}

QString QmlWeatherData::city() const
{
    return m_city;
}

QString QmlWeatherData::weatherIcon() const
{
    return m_weatherIcon;
}

QString QmlWeatherData::weatherDescription() const
{
    return m_weatherDescription;
}

QString QmlWeatherData::condition() const
{
    return m_condition;
}

int QmlWeatherData::maxTemperature() const
{
    return m_maxTemperature;
}

int QmlWeatherData::minTemperature() const
{
    return m_minTemperature;
}

double QmlWeatherData::pressure() const
{
    return m_pressure;
}

int QmlWeatherData::humidity() const
{
    return m_humidity;
}

void QmlWeatherData::setDayOfWeek(const QString &value)
{
    m_dayOfWeek = value;
    emit dataChanged();
}

void QmlWeatherData::setCity(const QString &value)
{
    m_city = value;
    emit dataChanged();
}

void QmlWeatherData::setWeatherIcon(const QString &value)
{
    m_weatherIcon = value;
    emit dataChanged();
}

void QmlWeatherData::setWeatherDescription(const QString &value)
{
    m_weatherDescription = value;
    emit dataChanged();
}

void QmlWeatherData::setCondition(const QString &value)
{
    m_condition = value;
    emit dataChanged();
}

void QmlWeatherData::setMaxTemperature(int value)
{
    m_maxTemperature = value;
    emit dataChanged();
}

void QmlWeatherData::setMinTemperature(int value)
{
    m_minTemperature = value;
    emit dataChanged();
}

void QmlWeatherData::setPressure(double value)
{
    m_pressure = value;
    emit dataChanged();
}

void QmlWeatherData::setHumidity(int value)
{
    m_humidity = value;
    emit dataChanged();
}
