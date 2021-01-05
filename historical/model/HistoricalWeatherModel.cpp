#include "HistoricalWeatherModel.hpp"

#include "historical/model/HistoricalWeatherParser.hpp"
#include "historical/model/HistoricalWeatherApi.hpp"

#include <QQmlEngine>

HistoricalWeatherModel::HistoricalWeatherModel(QObject* parent) :
    WeatherModel(std::make_unique<HistoricalWeatherApi>([&](){return std::make_pair(m_startDate, m_endDate);}),
                 std::make_unique<HistoricalWeatherParser>(),
                 parent)
{
    m_startDate = m_endDate = QDate::currentDate();
}

void HistoricalWeatherModel::request(const QDate& startDate, const QDate& endDate)
{
    m_startDate = startDate;
    m_endDate = endDate;
    api().requestByCity("Kharkiv");
}

void HistoricalWeatherModel::registerQmlType()
{
    qmlRegisterType<HistoricalWeatherModel>("HistoricalWeatherModel", 1, 0, "HistoricalWeatherModel");
}

void HistoricalWeatherModel::updateModel(const HistoricalWeatherData& data)
{
    if (data.days.size()) {
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

        const QString DateFormat("yyyy-MM-dd");
        m_temperatureMax = maxIt->maxTemperature;
        m_temperatureMin = minIt->minTemperature;
        m_tMaxDate = maxIt->date.toString(DateFormat);
        m_tMinDate = minIt->date.toString(DateFormat);
    }
    else {
        m_temperatureMin = m_temperatureMax = 0;
        m_tMinDate = m_tMaxDate = "";
    }
    m_city = data.city;

    m_temperatureDots.clear();
    for(auto&& day : data.days)
    {
        for(auto&& interval : day.timeIntervals)
        {
            m_temperatureDots.push_back(interval.temperature);
        }
    }

    emit maxTemperatureChanged(m_temperatureMax);
    emit minTemperatureChanged(m_temperatureMin);
    emit maxTemperatureDateChanged(m_tMaxDate);
    emit minTemperatureDateChanged(m_tMinDate);
    emit cityChanged(m_city);
    emit temperatureDotsChanged(m_temperatureDots);
}
