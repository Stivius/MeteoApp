#include "ResourcesIcons.hpp"
#include <map>

static std::map<QString, QUrl> LigthThemeMap
{
        { Icons::Keys::Sunny                , Icons::Paths::OldIcons::Sunny                }
    ,   { Icons::Keys::SunnyVeryFewClouds   , Icons::Paths::OldIcons::SunnyVeryFewClouds   }
    ,   { Icons::Keys::FewClouds            , Icons::Paths::OldIcons::FewClouds            }
    ,   { Icons::Keys::Overcast             , Icons::Paths::OldIcons::Overcast             }
    ,   { Icons::Keys::Showers              , Icons::Paths::OldIcons::Showers              }
    ,   { Icons::Keys::Thundershower        , Icons::Paths::OldIcons::ThunderShower        }
    ,   { Icons::Keys::Snow                 , Icons::Paths::OldIcons::Snow                 }
    ,   { Icons::Keys::Fog                  , Icons::Paths::OldIcons::Fog                  }
    ,   { Icons::Keys::Unknown              , Icons::Paths::OldIcons::Unknown              }
};


QUrl Icons::Resources::Utility::getIconUrl( const QString& iconId, ApplicationTheme theme )
{
    switch ( theme )
    {

    case ApplicationTheme::Dark:
    {
        return QUrl("");
    }
    break;

    case ApplicationTheme::Light:
    {
        if( auto it = LigthThemeMap.find( iconId ); it != LigthThemeMap.end() )
        {
            return it->second;
        }
        return LigthThemeMap.at("weather-unknown");
    }
    break;

    default:
    {
        Q_ASSERT(false);
        return QUrl("");
    }

    }
}
