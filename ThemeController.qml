pragma Singleton

import QtQuick 2.9
import CommonSettings 1.0
import ApplicationTheme 1.0

Item {

    property int currentAppTheme: AppThemeEnum.Dark

    function changeTheme( newTheme )
    {
        if( newTheme != currentAppTheme )
        {
            currentAppTheme = newTheme
            onThemeChanged( currentAppTheme )
        }
    }

    function onThemeChanged( newTheme )
    {
        weatherIconsProvider.CurrentTheme = currentAppTheme;

        switch( currentAppTheme )
        {
            case AppThemeEnum.Light:
            {
                CommonSettings.backgroundColor = CommonSettings.lightBackgroundColor
                CommonSettings.digitsColor = CommonSettings.lightDigitsColor
                CommonSettings.fontColor = CommonSettings.lightDigitsColor
            }
            return;

            case AppThemeEnum.Dark:
            {
                CommonSettings.backgroundColor = CommonSettings.darkBackgroundColor
                CommonSettings.digitsColor = CommonSettings.darkDigitsColor
                CommonSettings.fontColor = CommonSettings.darkDigitsColor
            }
            return;
        }
    }
}
