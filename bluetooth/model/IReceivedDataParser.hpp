#ifndef IRECEIVEDDATAPARSER_H
#define IRECEIVEDDATAPARSER_H

#include <QString>

class IReceivedDataParser
{
public:
    virtual ~IReceivedDataParser() = default;

public:

    virtual float getTemperature() const = 0;
    virtual float getPressure() const = 0;
    virtual float getHumidity() const = 0;

    virtual void tryParseValue( const QString& _toParse ) = 0;

};

#endif // IRECEIVEDDATAPARSER_H
