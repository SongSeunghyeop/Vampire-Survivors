#include "myResourceManager.h"
#include "GameOption.h"
#include "Time.h"
#include "myInput.h"
#include "myImage.h"

extern my::Application myapplication;

namespace my
{
	GameOption::GameOption()
	{

	}
	GameOption::~GameOption()
	{

	}
	void GameOption::Initialize()
	{
		black = ResourceManager::Load<Image>(L"Black", L"..\\Resources\\None.bmp");
		menuImg = ResourceManager::Load<Image>(L"Option", L"..\\Resources\\Option.bmp");
		GameObject::Initialize();
	}
	void GameOption::Update()
	{
		GameObject::Update();
	}
	void GameOption::Render(HDC hdc)
	{

		/*TransparentBlt(hdc, -1, -1, black->GetWidth(), black->GetHeight(),
			black->GetHdc(), 0, 0, black->GetWidth(), black->GetHeight(), RGB(255, 0, 255));*/

		TransparentBlt(hdc, 382, 65, menuImg->GetWidth(), menuImg->GetHeight(), 
			menuImg->GetHdc(), 0, 0, menuImg->GetWidth(), menuImg->GetHeight(), RGB(255,0,255));

		//BLENDFUNCTION func = {};
		//func.BlendOp = AC_SRC_OVER;
		//func.BlendFlags = 0;
		//func.AlphaFormat = 0; // 24비트면 0 써야함  // AC_SRC_ALPHA
		//func.SourceConstantAlpha = 30; // 0(투명) ~ 255(불투명) 알파값

		//AlphaBlend(hdc, 0, 0,
		//	black->GetWidth() * 100, black->GetHeight() * 100,
		//	black->GetHdc(), 0, 0,
		//	black->GetWidth(), black->GetHeight()
		//    , func);

		GameObject::Render(hdc);
	}
	void GameOption::Release()
	{
		GameObject::Release();
	}
}