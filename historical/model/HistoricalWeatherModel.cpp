#include "HistoricalWeatherModel.hpp"

#include "historical/model/HistoricalWeatherParser.hpp"
#include "historical/model/HistoricalWeatherApi.hpp"

#include <QQmlEngine>

HistoricalWeatherModel::HistoricalWeatherModel(QObject* parent) :
    WeatherModel(std::make_unique<HistoricalWeatherApi>([&](){return std::pair(m_startDate, m_finishDate);}),
                 std::make_unique<HistoricalWeatherParser>(),
                 parent)
{
}

void HistoricalWeatherModel::registerQmlType()
{
    qmlRegisterType<HistoricalWeatherModel>("HistoricalWeatherModel", 1, 0, "HistoricalWeatherModel");
}

void HistoricalWeatherModel::updateModel(const HistoricalWeatherData& data)
{
    auto maxIt = std::max_element(
            data.days.cbegin(),
            data.days.cend(),
            [](auto& left, auto& right) {
                return left.maxTemperature < right.maxTemperature;
            }
    );

    auto minIt = std::min_element(
            data.days.cbegin(),
            data.days.cend(),
            [](auto& left, auto& right) {
                 return left.minTemperature < right.minTemperature;
            }
    );

    const QString format("yyyy-MM-dd");
    m_temperatureMax = maxIt->maxTemperature;
    m_temperatureMin = minIt->minTemperature;
    m_tMaxDate = maxIt->date.toString(format);
    m_tMinDate = minIt->date.toString(format);

    emit maxTemperatureChanged(m_temperatureMax);
    emit minTemperatureChanged(m_temperatureMin);
    emit maxTemperatureDateChanged(m_tMaxDate);
    emit minTemperatureDateChanged(m_tMinDate);
}

void HistoricalWeatherModel::setDayDate(int day, int month, int year)
{
    m_startDate = QDate(year, month, day);
    m_finishDate = QDate(year, month, day);
}

void HistoricalWeatherModel::setWeekDate(int /*week*/, int /*year*/)
{
    /* Not implemented*/
}

void HistoricalWeatherModel::setMonthDate(int month, int year)
{
    m_startDate = QDate(year, month, 1);
    m_finishDate = QDate(year, month, m_startDate.daysInMonth());
}
