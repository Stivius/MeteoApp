#pragma once

#include <QObject>

#include "core/WeatherBaseApi.hpp"
#include "core/GeoPositioning.hpp"
#include "core/WeatherDataParser.hpp"
#include "core/GlobalSettings.hpp"

template <typename WeatherData, typename Base = QObject>
class WeatherModel : public Base
{
public:
    using ParserType = WeatherDataParser<WeatherData>;

    WeatherModel(std::unique_ptr<WeatherBaseApi>&& weatherApi,
                 std::unique_ptr<ParserType>&& dataParser,
                 QObject* parent = nullptr)  :
        Base(parent),
        m_weatherApi(std::move(weatherApi)),
        m_dataParser(std::move(dataParser))
    {
        QObject::connect(m_weatherApi.get(), &WeatherBaseApi::responseReceived, this, &WeatherModel::responseReceived);
        QObject::connect(m_weatherApi.get(), &WeatherBaseApi::error, this, &WeatherModel::responseError);

        QObject::connect(&GlobalSettings::get(), &GlobalSettings::locationChanged, this, &WeatherModel::locationChanged);
    }


public slots:
    void locationChanged(const QString& location)
    {
        qDebug() << "Location changed. Updating weather info...";
        m_weatherApi->requestByCity(location);
    }

protected:
    virtual void updateModel(const WeatherData& data) = 0;

    WeatherBaseApi& api()
    {
        return *m_weatherApi;
    }

private slots:
    void responseReceived(const QByteArray& response)
    {
        updateModel(m_dataParser->parse(response));
    }

    void responseError(const QString& error)
    {
        qDebug() << "API response error:" << error;
    }

private:
    std::unique_ptr<WeatherBaseApi> m_weatherApi;
    std::unique_ptr<ParserType> m_dataParser;

};
