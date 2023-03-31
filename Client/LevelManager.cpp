#include "LevelManager.h"
#include "myInput.h"

namespace my
{
	bool LevelManager::Level_Up;

	LevelManager::LevelManager()
	{
	
 	}
	LevelManager::~LevelManager()
	{

	}
	void LevelManager::Initialize()
	{
		level_bar = ResourceManager::Load<Image>(L"levelBar", L"..\\Resources\\InGameBar_.bmp");
		Charactor = ResourceManager::Load<Image>(L"charactor", L"..\\Resources\\Arca.bmp");
		health = ResourceManager::Load<Image>(L"health", L"..\\Resources\\health.bmp");
		health_zero = ResourceManager::Load<Image>(L"health_z", L"..\\Resources\\health_zero.bmp");
		Ex_value = ResourceManager::Load<Image>(L"Ex_value", L"..\\Resources\\Ex_value.bmp");
		menuImg = ResourceManager::Load<Image>(L"Option_LevelUp", L"..\\Resources\\Option_LevelUp.bmp");
		
		//Items
		Skills[0] = ResourceManager::Load<Image>(L"wind", L"..\\Resources\\wind.bmp");
		Skills[1] = ResourceManager::Load<Image>(L"blade", L"..\\Resources\\Blade.bmp");
		Skills[2] = ResourceManager::Load<Image>(L"Power_up", L"..\\Resources\\PowerUp.bmp");
		Skills[3] = ResourceManager::Load<Image>(L"Lightning_Item", L"..\\Resources\\Lightning_Item.bmp");

		selected_item = eItems::NONE;
	}
	void LevelManager::Update()
	{
		switch (selected_item)
		{
		case(eItems::WIND):
			speed_up();
			break;
		case(eItems::BLADE):
			blade_up();
			break;
		case(eItems::LIGHTNING):
			light_up();
			break;
		case(eItems::POWER_UP):
			power_up();
			break;
		}

	}

	//Item_List
	void LevelManager::speed_up()
	{
		Krochi::vel += 5;
		selected_item = eItems::NONE;
	}
	void LevelManager::blade_up()
	{
		Krochi::Blade_Power += 5;
		selected_item = eItems::NONE;
	}
	void LevelManager::light_up()
	{
		Krochi::Light_Power += 5;
		selected_item = eItems::NONE;
	}
	void LevelManager::power_up()
	{
		Krochi::Power += 5;
		selected_item = eItems::NONE;
	}

	void LevelManager::Render(HDC hdc)
	{
		TransparentBlt(hdc, 152, 5, level_bar->GetWidth(), level_bar->GetHeight(),
			level_bar->GetHdc(), 0, 0, level_bar->GetWidth(), level_bar->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 152, 5, Krochi::Exp, Ex_value->GetHeight(),
			Ex_value->GetHdc(), 0, 0, Krochi::Exp, Ex_value->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 15, 5, Charactor->GetWidth(), Charactor->GetHeight(),
			Charactor->GetHdc(), 0, 0, Charactor->GetWidth(), Charactor->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 22, 120, health_zero->GetWidth(), health_zero->GetHeight(),
			health_zero->GetHdc(), 0, 0, health_zero->GetWidth(), health_zero->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 22, 120, Krochi::Hp, health->GetHeight(),
			health->GetHdc(), 0, 0, health->GetWidth(), health->GetHeight(), RGB(255, 0, 255));

		if (LevelManager::Level_Up)
		{
			TransparentBlt(hdc, 382, 60, menuImg->GetWidth(), menuImg->GetHeight(),
				menuImg->GetHdc(), 0, 0, menuImg->GetWidth(), menuImg->GetHeight(), RGB(255, 0, 255));
			TransparentBlt(hdc, 397, 171, Skills[Num1]->GetWidth() * 2, Skills[Num1]->GetHeight() * 2,
				Skills[Num1]->GetHdc(), 0, 0, Skills[Num1]->GetWidth(), Skills[Num1]->GetHeight(), RGB(255, 0, 255));
			TransparentBlt(hdc, 397, 300, Skills[Num2]->GetWidth() * 2, Skills[Num2]->GetHeight() * 2,
				Skills[Num2]->GetHdc(), 0, 0, Skills[Num2]->GetWidth(), Skills[Num2]->GetHeight(), RGB(255, 0, 255));
			TransparentBlt(hdc, 397, 429, Skills[Num3]->GetWidth() * 2, Skills[Num3]->GetHeight() * 2,
				Skills[Num3]->GetHdc(), 0, 0, Skills[Num3]->GetWidth(), Skills[Num3]->GetHeight(), RGB(255, 0, 255));

			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				Vector2 mPos = Input::GetMousePos();

				if (mPos.x > 400 && mPos.x < 881
					&& mPos.y > 173 && mPos.y < 285) // Ã¹¹øÂ° Ä­
				{
					selected_item = (eItems)Num1;
				}
				if (mPos.x > 400 && mPos.x < 881
					&& mPos.y > 300 && mPos.y < 413) // µÎ¹øÂ° Ä­
				{
					selected_item = (eItems)Num2;
				}
				if (mPos.x > 400 && mPos.x < 881
					&& mPos.y > 430 && mPos.y < 543) // ¼¼¹øÂ° Ä­
				{
					selected_item = (eItems)Num3;
				}

				if (selected_item != eItems::NONE)
				{
					LevelManager::Level_Up = false;

					Krochi::mState = Krochi::ePlayerState::Idle;
				}
			}
		}
		if (!LevelManager::Level_Up)
		{
			Krochi::Blade_Time += Time::getDeltaTime();
			Krochi::Light_Time += Time::getDeltaTime();

			Num1 = rand() % 4; // 0~3

			while (Num2 == Num1)
				Num2 = rand() % 4;

			while(Num2 == Num3 || Num1 == Num3)
				Num3 = rand() % 4;
		}
	}
	void LevelManager::Release()
	{

	}
}