#pragma once

#include <hkUtilLib\String.h>

//////////////////////////////
// CONFIGURATION AND DEFINE

//------------------------------------------------------------------------------------
// Main application
#define AC_APP_NAME L"DirectX Engine"
#define AC_IS_FULL_SCREEN false
#define AC_WINDOW_WIDTH 800
#define AC_WINDOW_HEIGHT 600

//------------------------------------------------------------------------------------
// Framerate and FPS
#define AC_FRAME_PER_SECOND 60
#define AC_MAX_FRAME_SKIP 10

//------------------------------------------------------------------------------------
// Camera
#define AC_CAMERA_SPEED 20
#define AC_CAMERA_NEAR 1
#define AC_CAMERA_FAR 1000
#define AC_CAMERA_FOV 45

//------------------------------------------------------------------------------------
// Predefined
#define uint unsigned int

#define _PI 3.14159265358979323846


///////////////////
// APP RESOURCES
namespace AppResources
{
    ///////////////////////
    // APP CONFIGURATION
    namespace AppConfig
    {
        typedef enum APP_TRANSFORM_MATRIX
        {
            CAMERA_VIEW_MATRIX = 0,
            NUM_MATRIX
        } APP_TRANSFORM_MATRIX;
    }

    /////////////////////////////
    // STRUCT: ScreenResources
    struct ScreenRessources
    {
    public:
        ScreenRessources();

    public:
        uint screenWidth;
        uint screenHeight;

        uint windowWidth;
        uint windowHeight;

        bool isFullScreen;
    };

    // Global screen resources
    static ScreenRessources g_screenRess;
    ScreenRessources& GetScreenResources();

    //////////////////
    // APP CONSTANT
    namespace Constant
    {
    }
}

////////////////
// Predefined
#define AppConst AppResources::Constant