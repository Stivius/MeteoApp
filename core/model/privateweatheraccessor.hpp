#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>
#include <QtQml/QQmlListProperty>
#include <QtNetwork>
#include "QMLWeaterData.hpp"

class PrivateWeatherAccessor
{
public:

    explicit PrivateWeatherAccessor() = default;

    AWeatherData now;
    std::vector<std::unique_ptr<AWeatherData>> forecast;
    std::unique_ptr<QQmlListProperty<AWeatherData>> fcProp;
};
