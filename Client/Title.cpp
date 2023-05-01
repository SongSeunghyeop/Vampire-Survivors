 #include "Title.h"
#include "myResourceManager.h"
#include "Time.h"
#include "myInput.h"
#include "myImage.h"

namespace my
{
	bool Title::TitleUIButton;

	Title::Title()
	{
		font1 = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"돋움체");
		font2 = CreateFont(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"돋움체");
	}
	Title::~Title()
	{

	}
	void Title::Initialize()
	{
		titleImg = ResourceManager::Load<Image>(L"Title", L"..\\Resources\\intro4.bmp"); // 이미지의 키와 경로 정보를 받음
		start = ResourceManager::Load<Image>(L"start", L"..\\Resources\\Start_Button.bmp"); // 이미지의 키와 경로 정보를 받음
		start_M = ResourceManager::Load<Image>(L"start_M", L"..\\Resources\\Start_M.bmp"); // 이미지의 키와 경로 정보를 받음
		Exit_Button = ResourceManager::Load<Image>(L"Exit_Button", L"..\\Resources\\Exit_Button.bmp"); // 이미지의 키와 경로 정보를 받음
		Option_Button = ResourceManager::Load<Image>(L"option_button", L"..\\Resources\\Option_Button.bmp"); // 이미지의 키와 경로 정보를 받음
		Select_Button = ResourceManager::Load<Image>(L"Select_Button", L"..\\Resources\\Select_Button.bmp"); // 이미지의 키와 경로 정보를 받음
	}

	void Title::Update()
	{
		mPos = Input::GetMousePos();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (mPos.x > 557 && mPos.x < 557 + start->GetWidth() * 1.8
				&& mPos.y > 508 && mPos.y < 508 + start->GetHeight() * 1.8)
				TitleUIButton = true;
		}

		GameObject::Update();
	}
	void Title::Render(HDC hdc)
	
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		std::wstring mstart = L"시작";
		std::wstring moption = L"옵션";
		std::wstring mexit = L"나가기";
		std::wstring mep = L"강화";

		BitBlt(hdc, 0, 0, titleImg->GetWidth(), titleImg->GetHeight(), titleImg->GetHdc(), 0, 0, SRCCOPY);
		TransparentBlt(hdc, 547, 500, start->GetWidth() * 1.9, start->GetHeight() * 1.9, start->GetHdc(), 0, 0, start->GetWidth(), start->GetHeight(), RGB(184, 187, 185));
		TransparentBlt(hdc, 560, 625, Select_Button->GetWidth() * 1.8, Select_Button->GetHeight() * 1.8, Select_Button->GetHdc(), 0, 0, Select_Button->GetWidth(), Select_Button->GetHeight(), RGB(182, 185, 183));
	
		TransparentBlt(hdc, 402, 6, Exit_Button->GetWidth() * 2, Exit_Button->GetHeight() * 2, Exit_Button->GetHdc(), 0, 0, Exit_Button->GetWidth(), Exit_Button->GetHeight(), RGB(182, 185, 183));
		TransparentBlt(hdc, 790, 6, Option_Button->GetWidth() * 2, Option_Button->GetHeight() * 2, Option_Button->GetHdc(), 0, 0, Option_Button->GetWidth(), Option_Button->GetHeight(), RGB(184, 187, 185));
		 
		if (mPos.x > 557 && mPos.x < 557 + start->GetWidth() * 1.8
			&& mPos.y > 508 && mPos.y < 508 + start->GetHeight() * 1.8)
		{
			TransparentBlt(hdc, 542, 498, start->GetWidth() * 2, start->GetHeight() * 2, start->GetHdc(), 0, 0, start->GetWidth(), start->GetHeight(), RGB(184, 187, 185));
		}

		oldfont = (HFONT)SelectObject(hdc, font1);
		TextOut(hdc, 615, 519, mstart.c_str(), mstart.length());
		SelectObject(hdc, oldfont);
		oldfont = (HFONT)SelectObject(hdc, font2);
		TextOut(hdc, 821, 25, moption.c_str(), moption.length());
		TextOut(hdc, 422, 25, mexit.c_str(), mexit.length());
		TextOut(hdc, 625, 642, mep.c_str(), mep.length());
		SelectObject(hdc, oldfont);

		GameObject::Render(hdc);
	}
	void Title::Release()
	{
		DeleteObject(font1);
		DeleteObject(font2);

		GameObject::Release();
	}
}