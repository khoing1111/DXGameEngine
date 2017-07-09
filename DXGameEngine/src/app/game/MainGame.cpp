#include "MainGame.h"

#include "../AppResources.h"


//=============================================================================
#pragma region // Main game
//=============================================================================

//////////////
// CONSTANT
const int MainGame::TICKS_PER_FRAME = 1000 / AC_FRAME_PER_SECOND;
const float MainGame::SECOND_PER_FRAME = (float)MainGame::TICKS_PER_FRAME / 1000.0f;

////////////
// METHOD
MainGame::MainGame()
{
    m_lastGameTick = 0;
}

MainGame::MainGame(const MainGame& clone)
{

}

MainGame::~MainGame()
{
    Shutdown();
}

bool MainGame::Initialize(HWND hwnd, InputCore::KMInputManager& inputManager)
{
    // Create Render manager
    if (!m_renderManager.Initialize(hwnd))
        return false;

    m_renderManager.IntitializeMatrixList(AppResources::AppConfig::NUM_MATRIX);

    // Intitialize camera manager
    AppResources::ScreenRessources& screenResources = AppResources::GetScreenResources();
    m_cameraManager.Initialize(inputManager, 
                               screenResources.windowWidth, 
                               screenResources.windowHeight);
    m_renderManager.SetTransformMatrix(AppResources::AppConfig::CAMERA_VIEW_MATRIX,
                                       m_cameraManager.GetViewMatrix());

    // Create and initialize object manager
    m_objectManager.Initialize();

    return true;
}

bool MainGame::UpdateFrame()
{
    if (m_lastGameTick == 0)
    {
        m_lastGameTick = GetTickCount();
    }

    int loops = 0;
    while (GetTickCount() > m_lastGameTick && loops++ < AC_MAX_FRAME_SKIP) {
        Update();

        m_lastGameTick += TICKS_PER_FRAME;
    }

    bool success = Render();

    return true;
}

void MainGame::Update()
{
    // Update camera
    if (m_cameraManager.Update())
        m_renderManager.SetTransformMatrix(AppResources::AppConfig::CAMERA_VIEW_MATRIX,
                                           m_cameraManager.GetViewMatrix());

    // Update all objects
    m_objectManager.Update(MainGame::SECOND_PER_FRAME);
}

bool MainGame::Render()
{
    m_renderManager.Begin(hkRGBAColor::GRAY);

    // Render all objects
    m_objectManager.Render(m_renderManager);

    m_renderManager.SetDrawColor(hkRGBAColor::YELLOW);
    m_renderManager.DrawPoint(hkVector2F(0, 0), 3);

    if (!m_renderManager.End())
        return false;

    return true;
}

void MainGame::Shutdown()
{
}

//=============================================================================
#pragma endregion // Main game
//=============================================================================