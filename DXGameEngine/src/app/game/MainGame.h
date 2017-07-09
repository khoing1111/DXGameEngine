#pragma once

/////////////
// INCLUDE
#include <DXEngine\manager\render\RenderManager.h>
#include <DXEngine\manager\input\InputManager.h>
#include <DXEngine\manager\camera\CameraManager.h>

#include <hkUtilLib\core\Matrix.h>
#include <hkUtilLib\core\Vector.h>

#include "core\object\ObjectCore.h"
#include "manager\ObjectManager.h"

//////////////////////////
// Input event callback


/////////////////////
// CLASS: MainGame
class MainGame
{
    //////////////
    // CONSTANT
private:
    static const int TICKS_PER_FRAME;
    static const float SECOND_PER_FRAME;


    ///////////////////
    // METHOD MEMBER
public:
    MainGame();
    MainGame(const MainGame&);
    ~MainGame();

    bool Initialize(HWND, InputCore::KMInputManager& inputManager);
    bool UpdateFrame();
    void Shutdown();

private:
    void Update();
    bool Render();

private:
    RenderManager::D2DManager m_renderManager;
    GameCore::ObjectManager m_objectManager;
    GameCore::CameraManager m_cameraManager;

    DWORD m_lastGameTick;
};



////////////
// DEFINE
#define GetCameraResources GameResources::GetCameraRes