import QtQuick 2.9

import BluetoothWindowSettings 1.0
import FontSizes 1.0
import CommonSettings 1.0

Item {

    property string errorMessage: ""
    property string infoMessage: ""
    property real messageHeight: msgRect.height
    property bool hasError: errorMessage != ""
    property bool hasInfo: infoMessage != ""
    property bool isAnimationCompleted: true;
    function init() {
    }

    function close() {
        app.prevPage()
    }

    Rectangle {
        id: msgRect
        //anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: BluetoothWindowSettings.fieldHeight
        color: hasError ? BluetoothWindowSettings.errorColor : BluetoothWindowSettings.infoColor
        opacity: 0.9
        visible: (hasError || hasInfo)&& !isAnimationCompleted

        Text {
            id: messageText
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            minimumPixelSize: 5
            font.pixelSize: FontSizes.smallFontSize
            font.family: CommonSettings.themeFont
            fontSizeMode: Text.Fit
            color: BluetoothWindowSettings.messageCenterTextColor
            text: hasError ? errorMessage : infoMessage
        }
    }

    Timer
     {
         id: expiringTimer
         interval : 1300
         running: true;

         onTriggered:
         {
             rectAnimation.start()
         }
     }
    Connections
    {
        target: messageText
        onTextChanged:
        {
            expiringTimer.restart();
            isAnimationCompleted = false;
        }
    }
    SequentialAnimation {
        id: rectAnimation
        PauseAnimation { duration: expiringTimer.interval * 0.2 }
        OpacityAnimator {
            id: rectOpacityAnimator
            target: msgRect;
            from: 0.9;
            to: 0;
            duration: expiringTimer.interval * 0.3
        }
    }
   Connections
   {
       target: rectAnimation
       onFinished:
       {
           rectOpacityAnimator.target.opacity = 0.9;
           isAnimationCompleted = true;
       }
   }
}
