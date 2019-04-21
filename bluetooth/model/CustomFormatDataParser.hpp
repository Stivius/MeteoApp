#pragma once

#include "IReceivedDataParser.hpp"

class CustomFormatDataParser
    :   public IReceivedDataParser
{
public:

    CustomFormatDataParser() = default;
    ~CustomFormatDataParser() override = default;

public:
    float getTemperature() const override;
    float getPressure() const override;
    float getHumidity() const override;

    void tryParseValue( const QString& _toParse ) override;

private:
    const QString PressureBegin = "PRESSURE_BEGIN";
    const QString PressureEnd = "PRESSURE_END";
    const QString TempBegin = "TEMP_BEGIN";
    const QString TempEnd = "TEMP_END";
    const QString HumidityBegin = "HUMIDITY_BEGIN";
    const QString HumidityEnd = "HUMIDITY_END";

   std::pair<int, int> getKeyIndexes(
            const QString& _dataSource
        ,   const QString& _searchKeyBegin
        ,   const QString& _searchKeyEnd
    );

   float getFloatFromRange( const QString& _dataSource, int _keyBegin, int _keyEnd );
   bool isDataValid( const QString& _toParse ) const;

private:
    float m_humidity;
    float m_pressure;
    float m_temperature;
};
