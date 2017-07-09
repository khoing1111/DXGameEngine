#include "AppCore.h"
#include "AppResources.h"


////////////
// GLOBAL
AppCore::AppImpl* g_instance = nullptr;


//=============================================================================
#pragma region // Application Impliment class
//=============================================================================

////////////
// STATIC
AppCore::AppImpl* AppCore::AppImpl::GetInstance()
{
    return g_instance;
}

void AppCore::AppImpl::ReleaseInstance()
{
    if (g_instance)
    {
        delete g_instance;
    }

    g_instance = nullptr;
}

//=============================================================================
#pragma region // Application Impliment class
//=============================================================================



//=============================================================================
#pragma region // Win32AppImkl class
//=============================================================================

////////////
// STATIC
bool AppCore::Win32AppImpl::CreateInstance()
{
    if (!g_instance)
    {
        g_instance = new Win32AppImpl();
        if (!g_instance->Initialize())
        {
            ReleaseInstance();
            return false;
        }
    }

    return true;
}


////////////
// MEMBER
AppCore::Win32AppImpl::Win32AppImpl()
{
    m_isRunning = false;
}

AppCore::Win32AppImpl::Win32AppImpl(const Win32AppImpl* clone)
{

}

AppCore::Win32AppImpl::~Win32AppImpl()
{
    Release();
}

//-----------------------------------------------------------------------------
// Inherit class
bool AppCore::Win32AppImpl::Initialize()
{
    InitializeWindows();

    // Create input manager
    m_inputManager.Initialize();

    // Create game instance
    if (!m_mainGame.Initialize(m_hwnd, m_inputManager))
        return false;

    return true;
}

void AppCore::Win32AppImpl::Release()
{
    // Shutdown game
    m_mainGame.Shutdown();

    // Shutdown window
    ShutdownWindows();
}

void AppCore::Win32AppImpl::Run()
{
    m_isRunning = true;
    while (m_isRunning)
    {
        // Update input
        UpdateInput();

        if (!UpdateFrame())
        {
            m_isRunning = false;
        }
    }
}
//-----------------------------------------------------------------------------

bool AppCore::Win32AppImpl::UpdateFrame()
{
    // Update game
    if (!m_mainGame.UpdateFrame())
        return false;

    return true;
}

void AppCore::Win32AppImpl::UpdateInput()
{
    MSG msg;


    // Initialize the message structure.
    ZeroMemory(&msg, sizeof(MSG));

    // Handle the windows messages.
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    m_inputManager.Update();

    // If windows signals to end the application then exit out.
    if (msg.message == WM_QUIT || m_inputManager.IsKeyDown(VK_ESCAPE))
    {
        m_isRunning = false;
    }
}

LRESULT CALLBACK AppCore::Win32AppImpl::HandleWindowMessages(HWND hwnd, UINT umsg,
                                                             WPARAM wparam, LPARAM lparam)
{

    switch (umsg)
    {
        // Check if a key has been pressed on the keyboard.
    case WM_KEYDOWN:
        m_inputManager.KeyDown((unsigned int)wparam);
        return 0;

        // Check if a key has been released on the keyboard.
    case WM_KEYUP:
        m_inputManager.KeyUp((unsigned int)wparam);
        return 0;

    case WM_MOUSEWHEEL:
        int zDelta = GET_WHEEL_DELTA_WPARAM(wparam);
        m_inputManager.MouseWheelChange(zDelta);
    }


    //-----------------------------------------------------------------------------------------------------
    int x = GET_X_LPARAM(lparam);
    int y = GET_Y_LPARAM(lparam);

    switch (umsg)
    {
    case WM_LBUTTONDOWN:
        m_inputManager.LMouseDown(x, y);
        return 0;

    case WM_RBUTTONDOWN:
        m_inputManager.RMouseDown(x, y);
        return 0;

    case WM_MBUTTONDOWN:
        m_inputManager.MMouseDown(x, y);
        return 0;

    case WM_LBUTTONUP:
        m_inputManager.LMouseUp(x, y);
        return 0;

    case WM_RBUTTONUP:
        m_inputManager.RMouseUp(x, y);
        return 0;

    case WM_MBUTTONUP:
        m_inputManager.MMouseUp(x, y);
        return 0;

    case WM_MOUSEMOVE:
        m_inputManager.MouseMove(x, y);
        return 0;

        // Any other messages send to the default message handler as our application won't make use of them.
    default:
        return DefWindowProc(hwnd, umsg, wparam, lparam);
    }
}

void AppCore::Win32AppImpl::InitializeWindows()
{
    WNDCLASSEX wc;
    DEVMODE dmScreenSettings;
    int screenWidth, screenHeight, windowWidth, windowHeight;
    int posX, posY;

    AppResources::ScreenRessources& screenResources = AppResources::GetScreenResources();
    screenResources.isFullScreen = AC_IS_FULL_SCREEN;

    // Get the instance of this application.
    m_hinstance = GetModuleHandle(NULL);

    // Give the application a name.
    m_applicationName = AC_APP_NAME;

    // Setup the windows class with default settings.
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc<Win32AppImpl>;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_hinstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = m_applicationName;
    wc.cbSize = sizeof(WNDCLASSEX);

    // Register the window class.
    RegisterClassEx(&wc);

    // Determine the resolution of the clients desktop screen.
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    screenResources.screenWidth = screenWidth;
    screenResources.screenHeight = screenHeight;

    // Setup the screen settings depending on whether it is running in full screen or in windowed mode.
    if (screenResources.isFullScreen)
    {
        // If full screen set the screen to maximum size of the users desktop and 32bit.
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = (ulong)screenWidth;
        dmScreenSettings.dmPelsHeight = (ulong)screenHeight;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // Change the display settings to full screen.
        ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

        // Set the position of the window to the top left corner.
        posX = posY = 0;

        windowWidth = screenWidth;
        windowHeight = screenHeight;
    }
    else
    {
        // If windowed then set it to 800x600 resolution.
        windowWidth = AC_WINDOW_WIDTH;
        windowHeight = AC_WINDOW_HEIGHT;

        // Place the window in the middle of the screen.
        posX = (screenWidth - windowWidth) / 2;
        posY = (screenHeight - windowHeight) / 2;
    }

    // Save window size
    screenResources.windowWidth = windowWidth;
    screenResources.windowHeight = windowHeight;

    // Create the window with the screen settings and get the handle to it.
    m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
                            WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
                            posX, posY, windowWidth, windowHeight, NULL, NULL, m_hinstance, NULL);

    // Bring the window up on the screen and set it as main focus.
    ShowWindow(m_hwnd, SW_SHOW);
    SetForegroundWindow(m_hwnd);
    SetFocus(m_hwnd);
}

void AppCore::Win32AppImpl::ShutdownWindows()
{
    // Fix the display settings if leaving full screen mode.
    if (AppResources::GetScreenResources().isFullScreen)
    {
        ChangeDisplaySettings(NULL, 0);
    }

    // Remove the window.
    DestroyWindow(m_hwnd);
    m_hwnd = NULL;

    // Remove the application instance.
    UnregisterClass(m_applicationName, m_hinstance);
    m_hinstance = NULL;
}

//=============================================================================
#pragma endregion // Win32AppImkl class
//=============================================================================