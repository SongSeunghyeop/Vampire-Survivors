#include "myResourceManager.h"
#include "GameOption.h"
#include "Time.h"
#include "myInput.h"
#include "myImage.h"

extern my::Application myapplication;

namespace my
{
	float GameOption::sound_v1;
	float GameOption::sound_v2;

	GameOption::GameOption()
	{
		font1 = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"µ¸¿òÃ¼");
		font2 = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"µ¸¿òÃ¼");
	}
	GameOption::~GameOption()
	{

	}
	void GameOption::Initialize()
	{
		button_pos1 = 680;
		button_pos2 = 680;

		sound_v1 = (button_pos1 - 553) / 207 * 100;
		sound_v2 = (button_pos2 - 553) / 207 * 100;

		black = ResourceManager::Load<Image>(L"Black", L"..\\Resources\\None.bmp");
		menuImg = ResourceManager::Load<Image>(L"Option", L"..\\Resources\\Option.bmp");
		sound_line = ResourceManager::Load<Image>(L"sound_line", L"..\\Resources\\sound_line.bmp");
		sound_button = ResourceManager::Load<Image>(L"sound_button", L"..\\Resources\\sound_button.bmp");

		GameObject::Initialize();
	}
	void GameOption::Update()
	{
		mPos = Input::GetMousePos();

		sound_v1 = (button_pos1 - 553) / 207 * 100;
		sound_v2 = (button_pos2 - 553) / 207 * 100;

		if (Input::GetKey(eKeyCode::LBUTTON))
		{
			if (mPos.x > button_pos1 && mPos.x < button_pos1 + sound_button->GetWidth() * 2
				&& mPos.y > 260 && mPos.y < 260 + sound_button->GetHeight() * 2)
			{
				Clicked = true;
			}

			if (mPos.x > button_pos2 && mPos.x < button_pos2 + sound_button->GetWidth() * 2
				&& mPos.y > 450 && mPos.y < 450 + sound_button->GetHeight() * 2)
			{
				Clicked = true;
			}
		}

		if (Clicked)
		{
			if (mPos.x > 553 && mPos.x < 760)
			{
				if(mPos.y > 260 && mPos.y < 260 + sound_button->GetHeight() * 2)
					button_pos1 = mPos.x;
				if (mPos.y > 450 && mPos.y < 450 + sound_button->GetHeight() * 2)
				button_pos2 = mPos.x;
			}

			if (mPos.x <= 553)
			{
				if (mPos.y > 260 && mPos.y < 260 + sound_button->GetHeight() * 2)
					button_pos1 = 553;
				if (mPos.y > 450 && mPos.y < 450 + sound_button->GetHeight() * 2)
					button_pos2 = 553;
			}

			if (mPos.x >= 760)
			{
				if (mPos.y > 260 && mPos.y < 260 + sound_button->GetHeight() * 2)
					button_pos1 = 760;
				if (mPos.y > 450 && mPos.y < 450 + sound_button->GetHeight() * 2)
					button_pos2 = 760;
			}

			if (Input::GetKeyUp(eKeyCode::LBUTTON))
			{
				Clicked = false;
			}
		}

		GameObject::Update();
	}
	void GameOption::Render(HDC hdc)
	{
		TransparentBlt(hdc, 391, 70, menuImg->GetWidth(), menuImg->GetHeight(),
			menuImg->GetHdc(), 0, 0, menuImg->GetWidth(), menuImg->GetHeight(), RGB(255,0,255));

		TransparentBlt(hdc, 575, 260, sound_line->GetWidth(), sound_line->GetHeight(),
			sound_line->GetHdc(), 0, 0, sound_line->GetWidth(), sound_line->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 575, 450, sound_line->GetWidth(), sound_line->GetHeight(),
			sound_line->GetHdc(), 0, 0, sound_line->GetWidth(), sound_line->GetHeight(), RGB(255, 0, 255));

		// 553 ~ 760
		TransparentBlt(hdc, button_pos1, 260, sound_button->GetWidth() * 2, sound_button->GetHeight() * 2,
			sound_button->GetHdc(), 0, 0, sound_button->GetWidth(), sound_button->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, button_pos2, 450, sound_button->GetWidth() * 2, sound_button->GetHeight() * 2,
			sound_button->GetHdc(), 0, 0, sound_button->GetWidth(), sound_button->GetHeight(), RGB(255, 0, 255));

		std::wstring text = L"¿É¼Ç";
		std::wstring text2 = L"»ç¿îµå";
		std::wstring text3 = L"À½¾Ç";

		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		oldfont = (HFONT)SelectObject(hdc, font1);
		TextOut(hdc, 614, 100, text.c_str(), text.length());
		oldfont = (HFONT)SelectObject(hdc, font2);
		TextOut(hdc, 425, 270, text2.c_str(), text2.length());
		TextOut(hdc, 425, 460, text3.c_str(), text3.length());
		SelectObject(hdc, oldfont);

		GameObject::Render(hdc);
	}
	void GameOption::Release()
	{
		GameObject::Release();
	}
}