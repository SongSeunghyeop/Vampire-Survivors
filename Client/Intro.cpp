#include "Intro.h"
#include "myResourceManager.h"
#include "myInput.h"
#include "Time.h"
#include "myImage.h"


namespace my
{
	double Intro::mSecond = 0.0f;

	Intro::Intro()
	{
	}
	Intro::~Intro()
	{

	}
	void Intro::Initialize()
	{
		titleImg = ResourceManager::Load<Image>(L"Intro", L"..\\Resources\\intro3.bmp"); // 이미지의 키와 경로 정보를 받음
		IntroM = ResourceManager::Load<Image>(L"IntroM", L"..\\Resources\\TestM.bmp"); // 이미지의 키와 경로 정보를 받음

		GameObject::Initialize();
	}
	void Intro::Update()
	{
		GameObject::Update();
	}
	void Intro::Render(HDC hdc)
	{
		StretchBlt(hdc, 0, 0, titleImg->GetWidth(), titleImg->GetHeight(), titleImg->GetHdc(), 0, 0, titleImg->GetWidth(), titleImg->GetHeight(),SRCCOPY);
		TransparentBlt(hdc, 405, 640, 500, 55, IntroM->GetHdc(), 0, 0, IntroM->GetWidth(), IntroM->GetHeight(), RGB(255, 0, 255));
		
		mSecond += 0.2f * Time::getDeltaTime();

		if (mSecond > 0.1f)
		{
			BitBlt(hdc, 0, 0, titleImg->GetWidth(), titleImg->GetHeight(), titleImg->GetHdc(), 0, 0, SRCCOPY);
		}
		if (mSecond > 0.2f)
		{
			mSecond = 0.00f;
		}

		GameObject::Render(hdc);
	}
	void Intro::Release()
	{
		GameObject::Release();
	}
}