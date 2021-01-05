#pragma once

#include "core/WeatherModel.hpp"
#include "historical/model/HistoricalWeatherData.hpp"

class HistoricalWeatherModel : public WeatherModel<HistoricalWeatherData>
{
    Q_OBJECT

    Q_PROPERTY(int maxTemperature MEMBER m_temperatureMax NOTIFY maxTemperatureChanged)
    Q_PROPERTY(int minTemperature MEMBER m_temperatureMin NOTIFY minTemperatureChanged)
    Q_PROPERTY(QString maxTemperatureDate MEMBER m_tMaxDate NOTIFY maxTemperatureDateChanged)
    Q_PROPERTY(QString minTemperatureDate MEMBER m_tMinDate NOTIFY minTemperatureDateChanged)
    Q_PROPERTY(QString city MEMBER m_city NOTIFY cityChanged)
    Q_PROPERTY(QList<int> temperatureDots MEMBER m_temperatureDots NOTIFY temperatureDotsChanged)

signals:
    void maxTemperatureChanged(int temperature);
    void minTemperatureChanged(int temperature);
    void maxTemperatureDateChanged(const QString& date);
    void minTemperatureDateChanged(const QString& date);
    void cityChanged(const QString& city);
    void temperatureDotsChanged(const QList<int>& dots);

public:
    HistoricalWeatherModel(QObject* parent = nullptr);

    Q_INVOKABLE void request(const QDate& startDate, const QDate& endDate);

    static void registerQmlType();

protected:
    void updateModel(const HistoricalWeatherData& data) override;

private:
    int m_temperatureMax = 0;
    int m_temperatureMin = 0;
    QString m_tMaxDate;
    QString m_tMinDate;
    QString m_city;
    QList<int> m_temperatureDots;

private:
    QDate m_startDate;
    QDate m_endDate;

};
