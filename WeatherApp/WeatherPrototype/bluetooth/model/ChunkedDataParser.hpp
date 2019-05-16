#pragma once

#include "IReceivedDataParser.hpp"

class ChunkedDataParser
    :   public IReceivedDataParser
{
public:

    ChunkedDataParser() = default;
    ~ChunkedDataParser() override = default;

public:
    float getTemperature() const override;
    float getPressure() const override;
    float getHumidity() const override;

    void tryParseValue( const QString& _toParse ) override;

private:

    const QString Pressure = "pressure:";
    const QString Temp = "temp:";
    const QString Humidity= "hum:";

private:

    float getFloatValueByKey( const QString& _key , const QString& _getFrom );
private:

    float m_humidity;
    float m_pressure;
    float m_temperature;
};
