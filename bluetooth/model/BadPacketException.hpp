#pragma once

#include <QException>

class BadPacketException
        :   public QException
{

public:

    BadPacketException( const QString _exceptionMsg )
        :   m_execeptionMessage{ _exceptionMsg }
    {
    }

    ~BadPacketException() override =default;

    void raise () const override
    {
        throw *this;
    }

    BadPacketException *clone() const override
    {
        return new BadPacketException(*this);
    }

    QString getMessage() const
    {
        return m_execeptionMessage;
    }

private:

    QString m_execeptionMessage;

};
