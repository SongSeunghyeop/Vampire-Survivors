#include "GameOver.h"
#include "myResourceManager.h"
#include "myInput.h"
#include "Time.h"
#include "myImage.h"

namespace my
{
	GameOver::GameOver()
	{
		mexit =  CreateFont(26, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"돋움체");
	}
	GameOver::~GameOver()
	{

	}
	void GameOver::Initialize()
	{
		gameover = ResourceManager::Load<Image>(L"gameOver", L"..\\Resources\\gameOver.bmp"); // 이미지의 키와 경로 정보를 받음
		exit_Button = ResourceManager::Load<Image>(L"exit_Button2", L"..\\Resources\\Exit_Button2.bmp"); // 이미지의 키와 경로 정보를 받음

		GameObject::Initialize();
	}
	void GameOver::Update()
	{
		mPos = Input::GetMousePos();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (mPos.x > 563 && mPos.x < 563 + exit_Button->GetWidth() * 1.6
				&& mPos.y > 500 && mPos.y < 500 + exit_Button->GetWidth() * 1.6)
			{
				go_back = true;
			}
		}

		GameObject::Update();
	}
	void GameOver::Render(HDC hdc)
	{
		TransparentBlt(hdc, 434, 150, gameover->GetWidth() * 1.3, gameover->GetHeight() * 1.3, gameover->GetHdc(), 0, 0, gameover->GetWidth(), gameover->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 563, 500, exit_Button->GetWidth() * 1.6, exit_Button->GetHeight() * 1.6, exit_Button->GetHdc(), 0, 0, exit_Button->GetWidth(), exit_Button->GetHeight(), RGB(182, 185, 183));
		
		std::wstring mstart = L"나가기";

		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);
		oldfont = (HFONT)SelectObject(hdc, mexit);
		TextOut(hdc, 609, 515, mstart.c_str(), mstart.length());

		GameObject::Render(hdc);
	}
	void GameOver::Release()
	{
		GameObject::Release();
	}
}