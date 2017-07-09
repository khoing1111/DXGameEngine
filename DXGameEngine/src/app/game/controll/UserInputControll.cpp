#include "UserInputControll.h"

//==================================================================================================
#pragma region // Camera controller
//==================================================================================================
// 
UserInputControll::UserInputControll()
{
	m_inputManager = nullptr;

	m_keyDownCallback = nullptr;
	m_keyUpCallback = nullptr;
}

UserInputControll::UserInputControll(const UserInputControll& clone)
{
	m_inputManager = clone.m_inputManager;

	Initialize(m_inputManager);
}

UserInputControll::~UserInputControll()
{
	m_inputManager = nullptr;

	m_keyDownCallback = nullptr;
	m_keyUpCallback = nullptr;
}

void UserInputControll::Initialize(InputCore::KMInputManager* inputManager)
{
	m_inputManager = inputManager;

	SetupCallback();
}

void UserInputControll::Update()
{
	
}

void UserInputControll::SetupCallback()
{
	m_keyDownCallback = new OnKeyDown(this);
	m_keyUpCallback = new OnKeyUp(this);

	m_inputManager->OnKeyDown(m_keyDownCallback);
	m_inputManager->OnKeyUp(m_keyUpCallback);
}

void UserInputControll::HaltControll()
{
	m_keyDownCallback->Disable();
	m_keyUpCallback->Disable();
}

void UserInputControll::ResumeControll()
{
	m_keyDownCallback->Enable();
	m_keyUpCallback->Enable();
}

//==================================================================================================
#pragma endregion // Camera controller
//==================================================================================================


//==================================================================================================
 #pragma region // Event callback
//==================================================================================================

UserInputControll::OnKeyDown::OnKeyDown(UserInputControll* controll)
{
	m_controll = controll;
}

bool UserInputControll::OnKeyDown::OnCall(const InputCore::IEKeyboardEventArgs& evnt)
{
	return true;
}

UserInputControll::OnKeyUp::OnKeyUp(UserInputControll* controll)
{
	m_controll = controll;
}

bool UserInputControll::OnKeyUp::OnCall(const InputCore::IEKeyboardEventArgs& evnt)
{
	return true;
}

//==================================================================================================
#pragma endregion // Event callback
//==================================================================================================
