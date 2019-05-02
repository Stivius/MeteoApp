#pragma once

#include <QObject>
#include <QDate>

#include "core/api/HistoricalWeatherApi.hpp"
#include "core/model/HistoricalWeatherWrappers.hpp"

class HistoricalWeatherModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString city READ city NOTIFY cityChanged)
    Q_PROPERTY(QString maxTemperature READ maxTemperature NOTIFY maxTemperatureChanged)
    Q_PROPERTY(QString minTemperature READ minTemperature NOTIFY minTemperatureChanged)
    Q_PROPERTY(QString maxTemperatureDate READ maxTemperatureDate NOTIFY maxTemperatureDateChanged)
    Q_PROPERTY(QString minTemperatureDate READ minTemperatureDate NOTIFY minTemperatureDateChanged)
    Q_PROPERTY(QList<int> temperatureDots READ temperatureDots NOTIFY temperatureDotsChanged)

signals:
    void cityChanged(const QString& city);
    void maxTemperatureChanged(const QString& temperature);
    void minTemperatureChanged(const QString& temperature);
    void maxTemperatureDateChanged(const QString& date);
    void minTemperatureDateChanged(const QString& date);
    void temperatureDotsChanged(const QList<int>& data);

public:
    HistoricalWeatherModel(QObject* parent = nullptr);

    Q_INVOKABLE void requestWeather(int day, int month, int year);

    QString city() const;
    QString maxTemperature() const;
    QString minTemperature() const;
    QString maxTemperatureDate() const;
    QString minTemperatureDate() const;
    QList<int> temperatureDots() const;

private:
    void updateModel(const HistoricalWeatherData& data);

    void setCity(const QString& city);
    void setMaxTemperature(const QString& temperature);
    void setMinTemperature(const QString& temperature);
    void setMaxTemperatureDate(const QString& date);
    void setMinTemperatureDate(const QString& date);
    void setTemperatureDots(const QList<int>& data);

private:
    HistoricalWeatherApi* m_dataSource = nullptr;

    QString m_city     = "Kharkiv";
    QString m_tMax     = "0";
    QString m_tMin     = "0";
    QString m_tMaxDate = {};
    QString m_tMinDate = {};

    QList<int> m_temperatureDots;
};
