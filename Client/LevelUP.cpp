#include "myResourceManager.h"
#include "LevelUp.h"
#include "Time.h"
#include "myInput.h"
#include "myImage.h"

extern my::Application myapplication;

namespace my
{
	Level_Up::Level_Up()
	{

	}
	Level_Up::~Level_Up()
	{

	}
	void Level_Up::Initialize()
	{
		black = ResourceManager::Load<Image>(L"Black", L"..\\Resources\\None.bmp");
		menuImg = ResourceManager::Load<Image>(L"Option_LevelUp", L"..\\Resources\\Option_LevelUp.bmp");
		wind = ResourceManager::Load<Image>(L"wind", L"..\\Resources\\wind.bmp");
		blade = ResourceManager::Load<Image>(L"blade", L"..\\Resources\\Blade.bmp");
		Power_up = ResourceManager::Load<Image>(L"Power_up", L"..\\Resources\\PowerUp.bmp");
		
		GameObject::Initialize();
	}
	void Level_Up::Update()
	{
		GameObject::Update();
	}
	void Level_Up::Render(HDC hdc)
	{
		if (On)
		{
			TransparentBlt(hdc, 382, 60, menuImg->GetWidth(), menuImg->GetHeight(),
				menuImg->GetHdc(), 0, 0, menuImg->GetWidth(), menuImg->GetHeight(), RGB(255, 0, 255));
			TransparentBlt(hdc, 397, 171, wind->GetWidth() * 2, wind->GetHeight() * 2,
				wind->GetHdc(), 0, 0, wind->GetWidth(), wind->GetHeight(), RGB(255, 0, 255));
			TransparentBlt(hdc, 397, 300, blade->GetWidth() * 2, blade->GetHeight() * 2,
				blade->GetHdc(), 0, 0, blade->GetWidth(), blade->GetHeight(), RGB(255, 0, 255));
			TransparentBlt(hdc, 397, 429, Power_up->GetWidth() * 2, Power_up->GetHeight() * 2,
				Power_up->GetHdc(), 0, 0, Power_up->GetWidth(), Power_up->GetHeight(), RGB(255, 0, 255));
		}

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
	void Level_Up::Release()
	{
		GameObject::Release();
	}
}