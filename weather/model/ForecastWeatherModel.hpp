#pragma once

#include "core/WeatherModel.hpp"

#include <QAbstractListModel>

class ForecastWeatherModel : public WeatherModel<ForecastWeatherModel, QAbstractListModel>
{
    Q_OBJECT
    Q_ENUMS(ForecastRoles)

signals:
    void forecastChanged(const QVariantList& forecast);

public:
    enum ForecastRoles {
        DayOfWeek = Qt::UserRole + 1,
        MinTemperature,
        MaxTemperature,
        WeatherIcon
    };

    ForecastWeatherModel(QObject* parent = nullptr);

    static void registerQmlType();

    QHash<int,QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

protected:
    void updateModel(const WeatherDataCollection& data) override;

private:
    bool isIndexValid(const QModelIndex& index) const;

private:
    WeatherDataCollection m_forecast;

};

