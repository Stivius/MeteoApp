#include "ForecastWeatherModel.hpp"

#include "weather/model/ForecastWeatherApi.hpp"
#include "weather/model/ForecastWeatherParser.hpp"

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

QHash<int, QByteArray> ForecastWeatherModel::roleNames() const
{
    return {
        { DayOfWeek, "dayOfWeek" },
        { MinTemperature, "minTemperature" },
        { MaxTemperature, "maxTemperature" },
        { WeatherIcon, "weatherIcon" },
    };
}

int ForecastWeatherModel::rowCount(const QModelIndex&) const
{
    return m_forecast.size();
}

QVariant ForecastWeatherModel::data(const QModelIndex& index, int role) const
{
    if(!isIndexValid(index)) return QVariant{};

    auto data = m_forecast.at(index.row());
    switch (role)
    {
        case ForecastRoles::DayOfWeek:
            return data.dayOfTheWeek;
        case ForecastRoles::MinTemperature:
            return data.temperatureMin;
        case ForecastRoles::MaxTemperature:
            return data.temperatureMax;
        case ForecastRoles::WeatherIcon:
            return data.weatherIcon;
    }

    return QVariant{};
}

void ForecastWeatherModel::updateModel(const WeatherDataCollection& data)
{
    beginResetModel();

    m_forecast = std::move(data);

    endResetModel();
}

bool ForecastWeatherModel::isIndexValid(const QModelIndex& index) const
{
    if (!index.isValid())
        return false;

    int forecastCount = static_cast<int>(m_forecast.size());
    if (index.row() >= forecastCount || index.row() < 0)
        return false;

    return true;
}
