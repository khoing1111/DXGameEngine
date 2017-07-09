/////////////
// INCLUDE
#include "app/AppCore.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    // Create window 32 bit application core
    if (!AppCore::Win32AppImpl::CreateInstance())
        return 0;

    // Run win 32 application
    AppCore::AppImpl::GetInstance()->Run();

    // Release and shutdown application
    AppCore::AppImpl::ReleaseInstance();

    return 0;
}