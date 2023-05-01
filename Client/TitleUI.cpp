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
		titleImg = ResourceManager::Load<Image>(L"Title", L"..\\Resources\\intro4.bmp"); // 이미지의 키와 경로 정보를 받음
		SelectUI = ResourceManager::Load<Image>(L"Select", L"..\\Resources\\Select.bmp");
		start = ResourceManager::Load<Image>(L"start", L"..\\Resources\\Start_Button.bmp"); // 이미지의 키와 경로 정보를 받음
		start_M = ResourceManager::Load<Image>(L"start_M", L"..\\Resources\\Start_M.bmp"); // 이미지의 키와 경로 정보를 받음
		Selection = ResourceManager::Load<Image>(L"Selection", L"..\\Resources\\selection.bmp"); // 이미지의 키와 경로 정보를 받음
		Select_Button = ResourceManager::Load<Image>(L"Select_Button", L"..\\Resources\\Select_Button.bmp"); // 이미지의 키와 경로 정보를 받음

		font1 = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"돋움체");
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
			if (mPos.x > 1020 && mPos.x < 1020 + Select_Button->GetWidth() * 1.9
				&& mPos.y > 690 && mPos.y < 690 + Select_Button->GetWidth() * 1.9)
			{
				TitleUI::PlayButton = true;
			}
		}

		GameObject::Update();
	}
	void TitleUI::Render(HDC hdc)
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		std::wstring mstart = L"시작";

		Transform* trans = GetComponent<Transform>();
		Vector2 pos = trans->getPos();

		BitBlt(hdc, 0, 0, titleImg->GetWidth(), titleImg->GetHeight(), titleImg->GetHdc(), 0, 0, SRCCOPY);
		TransparentBlt(hdc, 340, 80, SelectUI->GetWidth(), SelectUI->GetHeight(), SelectUI->GetHdc(), 0, 0, SelectUI->GetWidth(), SelectUI->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 344, 157, Selection->GetWidth() * 2.5, Selection->GetHeight() * 2.5, Selection->GetHdc(), 0, 0, Selection->GetWidth(), Selection->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 1010, 683, Select_Button->GetWidth() * 1.9, Select_Button->GetHeight() * 1.9, Select_Button->GetHdc(), 0, 0, Select_Button->GetWidth(), Select_Button->GetHeight(), RGB(182, 185, 183));

		if (mPos.x > 1020 && mPos.x < 1020 + Select_Button->GetWidth() * 1.9
			&& mPos.y > 690 && mPos.y < 690 + Select_Button->GetWidth() * 1.9)
		{
			TransparentBlt(hdc, 1005, 681, Select_Button->GetWidth() * 2, Select_Button->GetHeight() * 2, Select_Button->GetHdc(), 0, 0, Select_Button->GetWidth(), Select_Button->GetHeight(), RGB(182, 185, 183));
		}

		oldfont = (HFONT)SelectObject(hdc, font1);
		TextOut(hdc, 1078, 701, mstart.c_str(), mstart.length());

		GameObject::Render(hdc);
	}
	void TitleUI::Release()
	{
		DeleteObject(font1);

		GameObject::Release();
	}
}