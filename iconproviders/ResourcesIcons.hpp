#pragma once

#include <QString>
#include <QUrl>

enum class ApplicationTheme
{
        Light
    ,   Dark
};

namespace Icons::Resources::Utility
{

    QUrl getIconUrl( const QString& iconId, ApplicationTheme theme );
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

namespace Icons::Paths::OldIcons
{
    const QUrl FewClouds            { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-few-clouds.png" )              };
    const QUrl Fog                  { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-fog.png" )                     };
    const QUrl Haze                 { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-haze.png" )                    };
    const QUrl Icy                  { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-icy.png" )                     };
    const QUrl Overcast             { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-overcast.png" )                };
    const QUrl Showers              { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-showers.png" )                 };
    const QUrl Sleet                { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-sleet.png" )                   };
    const QUrl Snow                 { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-snow.png" )                    };
    const QUrl Storm                { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-storm.png" )                   };
    const QUrl Sunny                { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-sunny.png" )                   };
    const QUrl SunnyVeryFewClouds   { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-sunny-very-few-clouds.png" )   };
    const QUrl ThunderShower        { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-thundershower.png" )           };
    const QUrl Unknown              { QUrl::fromLocalFile( ":/iconproviders/icons/old-icons/weather-unknown.png")                  };
}

