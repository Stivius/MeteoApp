#pragma once

#include <QString>
#include <QUrl>

#include "ApplicationTheme.hpp"

namespace Icons::Resources::Utility
{

    QString getIconPath( const QString& iconId, ApplicationTheme::Theme theme );
}

namespace Icons::Keys
{
    const QString Sunny              { "weather-sunny"                 };
    const QString SunnyVeryFewClouds { "weather-sunny-very-few-clouds" };
    const QString FewClouds          { "weather-few-clouds"            };
    const QString Overcast           { "weather-overcast"              };
    const QString Showers            { "weather-showers"               };
    const QString Thundershower      { "weather-thundershower"         };
    const QString Snow               { "weather-snow"                  };
    const QString Fog                { "weather-fog"                   };
    const QString Unknown            { "weather-unknown"               };
}

namespace Icons::Paths::ThemePath
{
    const QString DarkTheme = "dark-theme";
    const QString LightTheme = "light-theme";
    const QString OldIcons = "old-icons";
    const QString MatchRegex = "PROVIDER_FOLDER";
}

namespace Icons::Paths
{
    const QUrl FewClouds            { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-few-clouds.png" )              };
    const QUrl Fog                  { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-fog.png" )                     };
    const QUrl Haze                 { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-haze.png" )                    };
    const QUrl Icy                  { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-icy.png" )                     };
    const QUrl Overcast             { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-overcast.png" )                };
    const QUrl Showers              { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-showers.png" )                 };
    const QUrl Sleet                { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-sleet.png" )                   };
    const QUrl Snow                 { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-snow.png" )                    };
    const QUrl Storm                { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-storm.png" )                   };
    const QUrl Sunny                { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-sunny.png" )                   };
    const QUrl SunnyVeryFewClouds   { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-sunny-very-few-clouds.png" )   };
    const QUrl ThunderShower        { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-thundershower.png" )           };
    const QUrl Unknown              { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-unknown.png")                  };
}

