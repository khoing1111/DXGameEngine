#pragma once


///////////////////////////////
// PRE-PROCESSING DIRECTIVES
#define WIN32_LEAN_AND_MEAN


/////////////
// INCLUDE
#include "game/MainGame.h"

#include <DXEngine\manager\input\InputManager.h>
#include <Windows.h>
#include <windowsx.h>


namespace AppCore
{
    ///////////////////////
    // CLASS: AppImpl
    class AppImpl
    {
        ////////////
        // STATIC
    public:
        static AppImpl* GetInstance();
        static void ReleaseInstance();

        ///////////////////
        // METHOD MEMBER
    public:
        virtual bool Initialize() = 0;
        virtual void Release() = 0;

        virtual void Run() = 0;
    };


    ////////////
    // GLOBAL
    static AppImpl* g_instance;


    /////////////////////////
    // CLASS: Win32AppImpl
    class Win32AppImpl : public AppImpl
    {
        ////////////
        // STATIC
    public:
        static bool CreateInstance();


        ///////////////////
        // METHOD MEMBER
    public:
        Win32AppImpl();
        Win32AppImpl(const Win32AppImpl*);
        ~Win32AppImpl();

        //-------------------------------------------------------------------
        // Inherit class
        virtual bool Initialize() override;
        virtual void Release() override;

        virtual void Run() override;
        //-------------------------------------------------------------------

        LRESULT CALLBACK HandleWindowMessages(HWND, UINT, WPARAM, LPARAM);

    private:
        bool UpdateFrame();
        void UpdateInput();

        void InitializeWindows();
        void ShutdownWindows();


        //////////////
        // VARIABLE
    private:
        LPCWSTR m_applicationName;
        HINSTANCE m_hinstance;
        HWND m_hwnd;

        InputCore::KMInputManager m_inputManager;
        MainGame m_mainGame;

        bool m_isRunning;
    };



    /////////////////////////
    // FUNCTION PROTOTYPES
    // Use to handle window event message
    template <typename T>
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
    {
        switch (umessage)
        {
            // Check if the window is being destroyed.
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

            // Check if the window is being closed.
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;

            // All other messages pass to the message handler in the system class.
        default:
            return (static_cast <T*>(T::GetInstance()))->HandleWindowMessages(hwnd, umessage, wparam, lparam);
        }
    }
}