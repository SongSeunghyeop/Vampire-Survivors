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
					// ���� �����ӿ��� ���� �־���
					if (mKeys[i].bPressed)
						mKeys[i].Kstate = eKeyState::Pressed;
					else
						mKeys[i].Kstate = eKeyState::Down;

					mKeys[i].bPressed = true;
				}
				else // ���� �����ӿ� Ű�� �������� �ʴ�.
				{
					// ���� �����ӿ� ��Ű�� �����־���.
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