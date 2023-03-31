#include "myInput.h"
#include "myApplication.h"

extern my::Application myapplication;

namespace my
{
	int ASCII[(UINT)eKeyCode::END]
	{
		'W', 'A', 'S', 'D',
		'T', 'Y', 'U', 'I', 'O', 'P', 'Q', 
		'E', 'R', 'F', 'G', 'H', 'J', 'K', 
		'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_ESCAPE ,VK_RETURN , VK_SPACE , VK_LBUTTON,
	};

	std::vector<Input::Key> Input::mKeys = { };
	Vector2 Input::mMousePos = Vector2::Zero;

	void Input::Initialize()
	{
		for (int i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key keyInfo;
			keyInfo.Kcode = (eKeyCode)i;
			keyInfo.Kstate = eKeyState::None;
			keyInfo.bPressed = false;

			mKeys.push_back(keyInfo);
		}
	}

	void Input::Update()
	{
		if (GetFocus())
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에도 눌려 있었다
					if (mKeys[i].bPressed)
						mKeys[i].Kstate = eKeyState::Pressed;
					else
						mKeys[i].Kstate = eKeyState::Down;

					mKeys[i].bPressed = true;
				}
				else // 현재 프레임에 키가 눌려있지 않다.
				{
					// 이전 프레임에 내키가 눌려있엇다.
					if (mKeys[i].bPressed)
						mKeys[i].Kstate = eKeyState::Up;
					else
						mKeys[i].Kstate = eKeyState::None;

					mKeys[i].bPressed = false;
				}
			}

			POINT mousePos = {};
			GetCursorPos(&mousePos);

			ScreenToClient(myapplication.GetHwnd(), &mousePos);
			mMousePos.x = mousePos.x;
			mMousePos.y = mousePos.y;
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
			{
				if (eKeyState::Down == mKeys[i].Kstate
					|| eKeyState::Pressed == mKeys[i].Kstate)
				{
					mKeys[i].Kstate = eKeyState::Up;
				}
				else if (eKeyState::Up == mKeys[i].Kstate)
				{
					mKeys[i].Kstate = eKeyState::None;
				}

				mKeys[i].bPressed = false;
			}
		}
	}

	void Input::Render(HDC hdc)
	{

	}
}