#pragma once

#include "IReceivedDataParser.hpp"

class JsonFormatDataParser
    :   public IReceivedDataParser
{
public:

    JsonFormatDataParser() = default;
    ~JsonFormatDataParser() override = default;

public:
    float getTemperature() const override;
    float getPressure() const override;
    float getHumidity() const override;

    void tryParseValue( const QString& _toParse ) override;

private:

    const QString Pressure = "p";
    const QString Temp = "t";
    const QString Humidity= "h";

private:

    float m_humidity;
    float m_pressure;
    float m_temperature;
};
