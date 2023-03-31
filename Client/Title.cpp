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

	}
	Title::~Title()
	{

	}
	void Title::Initialize()
	{
		titleImg = ResourceManager::Load<Image>(L"Title", L"..\\Resources\\Title.bmp"); // 이미지의 키와 경로 정보를 받음
		start = ResourceManager::Load<Image>(L"start", L"..\\Resources\\Start_Button.bmp"); // 이미지의 키와 경로 정보를 받음
		start_M = ResourceManager::Load<Image>(L"start_M", L"..\\Resources\\Start_M.bmp"); // 이미지의 키와 경로 정보를 받음
		Exit_Button = ResourceManager::Load<Image>(L"Exit_Button", L"..\\Resources\\Exit_Button.bmp"); // 이미지의 키와 경로 정보를 받음

		Option_Button = ResourceManager::Load<Image>(L"option_button", L"..\\Resources\\Option_Button.bmp"); // 이미지의 키와 경로 정보를 받음
	}

	void Title::Update()
	{
		mPos = Input::GetMousePos();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (mPos.x > 1029 && mPos.x < 1029 + start->GetWidth() * 1.1
				&& mPos.y > 442 && mPos.y < 442 + start->GetHeight() * 1.1)
				TitleUIButton = true;
		}

		GameObject::Update();
	}
	void Title::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, titleImg->GetWidth(), titleImg->GetHeight(), titleImg->GetHdc(), 0, 0, SRCCOPY);
		TransparentBlt(hdc, 1020, 430, start->GetWidth() * 1.1, start->GetHeight() * 1.1, start->GetHdc(), 0, 0, start->GetWidth(), start->GetHeight(), RGB(255, 0, 255));
		//TransparentBlt(hdc, 1076, 440, start_M->GetWidth(), start_M->GetHeight() * 0.9, start_M->GetHdc(), 0, 0, start_M->GetWidth(), start_M->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 1020, 510, Option_Button->GetWidth() * 1.1, Option_Button->GetHeight() * 1.1, Option_Button->GetHdc(), 0, 0, Option_Button->GetWidth(), Option_Button->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 1020, 590, Exit_Button->GetWidth() * 1.1, Exit_Button->GetHeight() * 1.1, Exit_Button->GetHdc(), 0, 0, Exit_Button->GetWidth(), Exit_Button->GetHeight(), RGB(255, 0, 255));
		 
		if (mPos.x > 1029 && mPos.x < 1029 + start->GetWidth() * 1.1
			&& mPos.y > 442 && mPos.y < 442 + start->GetHeight() * 1.1)
		{
			TransparentBlt(hdc, 1012, 427, start->GetWidth() * 1.2, start->GetHeight() * 1.2, start->GetHdc(), 0, 0, start->GetWidth(), start->GetHeight(), RGB(255, 0, 255));
			//TransparentBlt(hdc, 1076, 439, start_M->GetWidth() * 1.1, start_M->GetHeight() , start_M->GetHdc(), 0, 0, start_M->GetWidth(), start_M->GetHeight(), RGB(255, 0, 255));
		}

		GameObject::Render(hdc);
	}
	void Title::Release()
	{
		GameObject::Release();
	}
}