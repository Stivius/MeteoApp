#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>
#include <QtQml/QQmlListProperty>
#include <QtNetwork>

#include "QmlWeatherData.hpp"

class PrivateWeatherAccessor
{
public:

    explicit PrivateWeatherAccessor() = default;

    QmlWeatherData now;
    std::vector<std::unique_ptr<QmlWeatherData>> forecast;
    std::unique_ptr<QQmlListProperty<QmlWeatherData>> fcProp;
};
