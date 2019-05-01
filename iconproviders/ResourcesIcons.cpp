#include "ResourcesIcons.hpp"
#include <map>
#include <QRegExp>

using IconsStore = std::map<QString, QUrl> ;

static IconsStore ThemeMap
{
        { Icons::Keys::Sunny                , Icons::Paths::Sunny                }
    ,   { Icons::Keys::SunnyVeryFewClouds   , Icons::Paths::SunnyVeryFewClouds   }
    ,   { Icons::Keys::FewClouds            , Icons::Paths::FewClouds            }
    ,   { Icons::Keys::Overcast             , Icons::Paths::Overcast             }
    ,   { Icons::Keys::Showers              , Icons::Paths::Showers              }
    ,   { Icons::Keys::Thundershower        , Icons::Paths::ThunderShower        }
    ,   { Icons::Keys::Snow                 , Icons::Paths::Snow                 }
    ,   { Icons::Keys::Fog                  , Icons::Paths::Fog                  }
    ,   { Icons::Keys::Unknown              , Icons::Paths::Unknown              }
};

namespace
{
    QString getUrlFromThemeMap(
        const QString& iconKey
    ,   const IconsStore& iconsHolder
    ,   const QString& regexFilter
    )

    {
        QString iconString;
        if( auto iconIt = iconsHolder.find( iconKey ); iconIt!= iconsHolder.end() )
            iconString= iconIt->second.toLocalFile();
        else
            iconString = iconsHolder.at( Icons::Keys::Unknown ).toLocalFile();

        QRegExp regex { Icons::Paths::ThemePath::MatchRegex };
        iconString.replace( regex, regexFilter );

        return iconString;
    }
}

QString Icons::Resources::Utility::getIconPath( const QString& iconId, ApplicationTheme::Theme theme )
{
    switch ( theme )
    {

    case ApplicationTheme::Theme::Dark:
    {
        return getUrlFromThemeMap( iconId, ThemeMap, Icons::Paths::ThemePath::DarkTheme );
    }
    break;

    case ApplicationTheme::Theme::Light:
    {
        return getUrlFromThemeMap( iconId, ThemeMap, Icons::Paths::ThemePath::LightTheme );
    }
    break;

    default:
    {
        Q_ASSERT(false);
        return QString("");
    }

    }
}
