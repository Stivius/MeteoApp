#pragma once

#include <QString>
#include <QUrl>
#include "ApplicationTheme.hpp"

using IconsStore = std::map<QString, QUrl>;

namespace Icons::Resources::Utility
{

    QString getIconPath(
            const QString& iconId
        ,   const IconsStore& iconsMap
        ,   const QString& unknownIconKey
        ,   ApplicationTheme::Theme theme
    );
}

namespace Icons::Weather::Keys
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

namespace Icons::Weather::Paths
{
    const QUrl FewClouds            { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-few-clouds.png" )              };
    const QUrl Fog                  { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-fog.png" )                     };
    const QUrl Haze                 { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-haze.png" )                    };
    const QUrl Icy                  { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-icy.png" )                     };
    const QUrl Overcast             { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-overcast.png" )                };
    const QUrl Showers              { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-showers.png" )                 };
    const QUrl Sleet                { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-sleet.png" )                   };
    const QUrl Snow                 { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-snow.png" )                    };
    const QUrl Storm                { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-storm.png" )                   };
    const QUrl Sunny                { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-sunny.png" )                   };
    const QUrl SunnyVeryFewClouds   { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-sunny-very-few-clouds.png" )   };
    const QUrl ThunderShower        { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-thundershower.png" )           };
    const QUrl Unknown              { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/weather-view/weather-unknown.png")                  };
}

namespace Icons::Bluetooth::Keys
{
    const QString Humidity              { "humidity-icon"               };
    const QString Pressure              { "pressure-icon"               };
    const QString Temperature           { "temperature-icon"            };
    const QString Unknown               { "unknown-icon"                };
}

namespace Icons::Bluetooth::Paths
{
    const QUrl Humidity                 { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/bluetooth-view/humidity.png" )                    };
    const QUrl Pressure                 { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/bluetooth-view/pressure.png" )                    };
    const QUrl Temperature              { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/bluetooth-view/temperature.png" )                 };
    const QUrl Unknown                  { QUrl::fromLocalFile( ":/iconproviders/icons/PROVIDER_FOLDER/bluetooth-view/unknown.png" )                     };
}

static IconsStore WeatherThemeMap
{
        { Icons::Weather::Keys::Sunny                , Icons::Weather::Paths::Sunny                }
    ,   { Icons::Weather::Keys::SunnyVeryFewClouds   , Icons::Weather::Paths::SunnyVeryFewClouds   }
    ,   { Icons::Weather::Keys::FewClouds            , Icons::Weather::Paths::FewClouds            }
    ,   { Icons::Weather::Keys::Overcast             , Icons::Weather::Paths::Overcast             }
    ,   { Icons::Weather::Keys::Showers              , Icons::Weather::Paths::Showers              }
    ,   { Icons::Weather::Keys::Thundershower        , Icons::Weather::Paths::ThunderShower        }
    ,   { Icons::Weather::Keys::Snow                 , Icons::Weather::Paths::Snow                 }
    ,   { Icons::Weather::Keys::Fog                  , Icons::Weather::Paths::Fog                  }
    ,   { Icons::Weather::Keys::Unknown              , Icons::Weather::Paths::Unknown              }
};

static IconsStore BluetoothThemeMap
{
        { Icons::Bluetooth::Keys::Humidity           , Icons::Bluetooth::Paths::Humidity           }
    ,   { Icons::Bluetooth::Keys::Pressure           , Icons::Bluetooth::Paths::Pressure           }
    ,   { Icons::Bluetooth::Keys::Temperature        , Icons::Bluetooth::Paths::Temperature        }
    ,   { Icons::Bluetooth::Keys::Unknown            , Icons::Bluetooth::Paths::Unknown            }
};
