#include "myResourceManager.h"
#include "TitleUI.h"
#include "mySceneManager.h"
#include "myInput.h"
#include "myImage.h"

namespace my
{
	bool TitleUI::PlayButton;

	TitleUI::TitleUI()
	{
		titleImg = ResourceManager::Load<Image>(L"Intro", L"..\\Resources\\Title3.bmp"); // 이미지의 키와 경로 정보를 받음
		SelectUI = ResourceManager::Load<Image>(L"Select", L"..\\Resources\\Select.bmp");
		info = ResourceManager::Load<Image>(L"info", L"..\\Resources\\Info.bmp");
		start = ResourceManager::Load<Image>(L"start", L"..\\Resources\\Start_Button.bmp"); // 이미지의 키와 경로 정보를 받음
		start_M = ResourceManager::Load<Image>(L"start_M", L"..\\Resources\\Start_M.bmp"); // 이미지의 키와 경로 정보를 받음
		Selection = ResourceManager::Load<Image>(L"Selection", L"..\\Resources\\selection.bmp"); // 이미지의 키와 경로 정보를 받음
		Select_Button = ResourceManager::Load<Image>(L"Select_Button", L"..\\Resources\\Select_Button.bmp"); // 이미지의 키와 경로 정보를 받음
	}
	TitleUI::~TitleUI()
	{

	}
	void TitleUI::Initialize()
	{
		GameObject::Initialize();
	}

	void TitleUI::Update()
	{
		mPos = Input::GetMousePos();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			if (mPos.x > 1020 && mPos.x < 1020 + Select_Button->GetWidth() * 1.1
				&& mPos.y > 643 && mPos.y < 643 + Select_Button->GetHeight() * 1.1)
				
				TitleUI::PlayButton = true;
		}
		GameObject::Update();
	}
	void TitleUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* trans = GetComponent<Transform>();
		Vector2 pos = trans->getPos();

		BitBlt(hdc, 0, 0, titleImg->GetWidth(), titleImg->GetHeight(), titleImg->GetHdc(), 0, 0, SRCCOPY);
		TransparentBlt(hdc, 340, 30, SelectUI->GetWidth(), SelectUI->GetHeight(), SelectUI->GetHdc(), 0, 0, SelectUI->GetWidth(), SelectUI->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 344, 107, Selection->GetWidth() * 2.5, Selection->GetHeight() * 2.5, Selection->GetHdc(), 0, 0, Selection->GetWidth(), Selection->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 50, 130, info->GetWidth() / 1.3, info->GetHeight() / 1.3, info->GetHdc(), 0, 0, info->GetWidth(), info->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 1010, 633, Select_Button->GetWidth() * 1.1, Select_Button->GetHeight() * 1.1, Select_Button->GetHdc(), 0, 0, Select_Button->GetWidth(), Select_Button->GetHeight(), RGB(255, 0, 255));

		if (mPos.x > 1020 && mPos.x < 1020 + Select_Button->GetWidth() * 1.1
			&& mPos.y > 643 && mPos.y < 643 + Select_Button->GetHeight() * 1.1)
		{
			TransparentBlt(hdc, 1002, 630, Select_Button->GetWidth() * 1.2, Select_Button->GetHeight() * 1.2, Select_Button->GetHdc(), 0, 0, Select_Button->GetWidth(), Select_Button->GetHeight(), RGB(255, 0, 255));
		}
	}
	void TitleUI::Release()
	{
		GameObject::Release();
	}
}