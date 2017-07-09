#pragma once

/////////////
// INCLUDE
#include <DXEngine\manager\input\InputManager.h>


//////////////////////////////
// CLASS: UserInputControll
class UserInputControll
{
private:
	///////////////////////////////////////
	// Mouse and keyboard event callback
	struct OnKeyDown : InputCore::IEKeyboardCallback
	{
	public:
		OnKeyDown(UserInputControll* controll);

	private:
		virtual bool OnCall(const InputCore::IEKeyboardEventArgs&) override;

	private:
		UserInputControll* m_controll;
	};

	struct OnKeyUp : InputCore::IEKeyboardCallback
	{
	public:
		OnKeyUp(UserInputControll* controll);

	private:
		virtual bool OnCall(const InputCore::IEKeyboardEventArgs&) override;

	private:
		UserInputControll* m_controll;
	};

public:
	UserInputControll();
	UserInputControll(const UserInputControll&);
	~UserInputControll();

	void Initialize(InputCore::KMInputManager*);
	void Update();

	void HaltControll();
	void ResumeControll();

private:
	void SetupCallback();

private:
	InputCore::KMInputManager* m_inputManager;

	OnKeyDown* m_keyDownCallback;
	OnKeyUp* m_keyUpCallback;
};

