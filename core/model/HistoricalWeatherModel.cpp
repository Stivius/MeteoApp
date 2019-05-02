#include "HistoricalWeatherModel.hpp"

HistoricalWeatherModel::HistoricalWeatherModel(QObject* parent) :
    QObject(parent), m_dataSource(new HistoricalWeatherApi())
{
    connect(m_dataSource, &HistoricalWeatherApi::weatherReceived, this, &HistoricalWeatherModel::updateModel);
}

void HistoricalWeatherModel::requestWeather(int day, int month, int year)
{
    m_dataSource->requestWeather(
            "Kharkiv"
        ,   HistoricalWeatherMode::Day
        ,   QDate(year, month, day)
        ,   QDate(year, month, day)
    );
}

QString HistoricalWeatherModel::city() const
{
    return m_city;
}

void HistoricalWeatherModel::setCity(const QString& cityName)
{
    m_city = cityName;
    emit cityChanged(cityName);
}

QString HistoricalWeatherModel::maxTemperature() const
{
    return m_tMax;
}

void HistoricalWeatherModel::setMaxTemperature(const QString& temperature)
{
    m_tMax = temperature;
    emit maxTemperatureChanged(temperature);
}

QString HistoricalWeatherModel::minTemperature() const
{
    return m_tMin;
}

void HistoricalWeatherModel::setMinTemperature(const QString& temperature)
{
    m_tMin = temperature;
    emit minTemperatureChanged(temperature);
}

QString HistoricalWeatherModel::maxTemperatureDate() const
{
    return m_tMaxDate;
}

void HistoricalWeatherModel::setMaxTemperatureDate(const QString& date)
{
    m_tMaxDate = date;
    emit maxTemperatureDateChanged(date);
}

QString HistoricalWeatherModel::minTemperatureDate() const
{
    return m_tMinDate;
}

void HistoricalWeatherModel::setMinTemperatureDate(const QString& date)
{
    m_tMinDate = date;
    emit minTemperatureDateChanged(date);
}

QList<int> HistoricalWeatherModel::temperatureDots() const
{
    return m_temperatureDots;
}

void HistoricalWeatherModel::setTemperatureDots(const QList<int>& data)
{
    m_temperatureDots = data;
    emit temperatureDotsChanged(data);
}

void HistoricalWeatherModel::updateModel(const HistoricalWeatherData& data)
{
    auto maxIt = std::max_element(
             data.days.cbegin()
        ,    data.days.cend()
        ,   [](const HistoricalWeatherDay& left, const HistoricalWeatherDay& right) -> bool
            {
                 return left.maxTemperature > right.maxTemperature;
            }
    );

    auto minIt = std::min_element(
             data.days.cbegin()
        ,    data.days.cend()
        ,   [](const HistoricalWeatherDay& left, const HistoricalWeatherDay& right) -> bool
            {
                 return left.minTemperature < right.minTemperature;
            }
    );

    QList<int> temperatureData;

    for(auto&& day : data.days)
    {
        for(auto&& interval : day.timeIntervals)
        {
            temperatureData.push_back(interval.temperature);
        }
    }

    setCity(data.city);
    setTemperatureDots(temperatureData);
    setMaxTemperature(QString::number(maxIt->maxTemperature));
    setMaxTemperatureDate(maxIt->date.toString("yyyy-MM-dd"));
    setMinTemperature(QString::number(minIt->minTemperature));
    setMinTemperatureDate(minIt->date.toString("yyyy-MM-dd"));
}
