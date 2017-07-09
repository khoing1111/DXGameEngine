#include "AppResources.h"


//===========================================================================================
#pragma region // Screen resources
//===========================================================================================

AppResources::ScreenRessources::ScreenRessources()
{
    screenWidth = AC_WINDOW_WIDTH;
    screenHeight = AC_WINDOW_HEIGHT;

    windowWidth = AC_WINDOW_WIDTH;
    windowHeight = AC_WINDOW_HEIGHT;

    isFullScreen = AC_IS_FULL_SCREEN;
}

AppResources::ScreenRessources& AppResources::GetScreenResources()
{
    return AppResources::g_screenRess;
}

//===========================================================================================
#pragma endregion // Screen resources
//===========================================================================================