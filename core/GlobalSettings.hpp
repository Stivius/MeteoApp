#pragma once

#include <QObject>

class GlobalSettings : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(GlobalSettings)

    Q_PROPERTY(QString location READ location WRITE setLocation)

signals:
    void locationChanged(const QString& location);

public:
    static GlobalSettings& get();

    void setLocation(const QString& location);
    QString location() const;

private:
    GlobalSettings(QObject* parent = nullptr);

private:
    QString m_location;

};
