#include "PlayerManager.h"
#include "myInput.h"
#include "myPlayScene.h"
namespace my
{
	bool PlayerManager::Level_Up;
	bool PlayerManager::Show_on;
	Krochi::eSkillState Krochi::skillState;

	PlayerManager::PlayerManager()
	{
		Play_Time = 0.0f;

		font1 = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Maplestory");
		font2 = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Maplestory");
 	}
	PlayerManager::~PlayerManager()
	{

	}
	void PlayerManager::Initialize()
	{
		level_bar = ResourceManager::Load<Image>(L"levelBar", L"..\\Resources\\InGameBar_.bmp");
		Charactor = ResourceManager::Load<Image>(L"charactor", L"..\\Resources\\Arca.bmp");
		health = ResourceManager::Load<Image>(L"health", L"..\\Resources\\health.bmp");
		health_zero = ResourceManager::Load<Image>(L"health_z", L"..\\Resources\\health_zero.bmp");
		Ex_value = ResourceManager::Load<Image>(L"Ex_value", L"..\\Resources\\Ex_value.bmp");
		menuImg = ResourceManager::Load<Image>(L"Option_LevelUp", L"..\\Resources\\Option_LevelUp.bmp");
		Item_list = ResourceManager::Load<Image>(L"Item_list", L"..\\Resources\\Item_list.bmp");
		Tresure_UI = ResourceManager::Load<Image>(L"Tresure_UI", L"..\\Resources\\Option.bmp");
		
		Tr = GetComponent<Transform>();

		Treasure_show = AddComponent<Animator>();
		Treasure_show->CreateAnimations(L"..\\Resources\\Treasures\\Show2", 0.075f);

		Skills = new Item_Info[8];

		//Items
		Skills[(int)eItems::WIND].item_image = ResourceManager::Load<Image>(L"wind", L"..\\Resources\\wind.bmp");
		Skills[(int)eItems::POWER_UP].item_image = ResourceManager::Load<Image>(L"Power_up", L"..\\Resources\\PowerUp.bmp");
		Skills[(int)eItems::LIGHTNING].item_image = ResourceManager::Load<Image>(L"Lightning_Item", L"..\\Resources\\Lightning_Item.bmp");
		Skills[(int)eItems::BOOK].item_image = ResourceManager::Load<Image>(L"Book_Item", L"..\\Resources\\Book_select.bmp");
		Skills[(int)eItems::ARMOR].item_image = ResourceManager::Load<Image>(L"Armor", L"..\\Resources\\armor.bmp");
		Skills[(int)eItems::EMEPY_BOOK].item_image = ResourceManager::Load<Image>(L"EmptyBook", L"..\\Resources\\Empty_Book.bmp");
		Skills[(int)eItems::CROSS].item_image = ResourceManager::Load<Image>(L"Cross_select", L"..\\Resources\\cross_select.bmp");
		Skills[(int)eItems::HEART].item_image = ResourceManager::Load<Image>(L"Heart", L"..\\Resources\\Heart.bmp");

		selected_item = eItems::NONE;

		GameObject::Initialize();
	}
	void PlayerManager::Update()
	{	 
		switch (selected_item)
		{
		case(eItems::WIND):
			speed_up();
			break;
		case(eItems::LIGHTNING):
			light_up();
			break;
		case(eItems::BOOK):
			book_up();
			break;
		case(eItems::ARMOR):
			armor_up();
			break;
		case(eItems::POWER_UP):
			power_up();
			break;
		case(eItems::EMEPY_BOOK):
			empty_book();
			break;
		case(eItems::CROSS):
			cross_up();
			break;
		case(eItems::HEART):
			heart_up();
			break;
		}

		if (PlayerManager::Level_Up || PlayerManager::Show_on)
		{
			Krochi::skillState = Krochi::eSkillState::Skill_Off;
		}
		if (!PlayerManager::Level_Up && !PlayerManager::Show_on)
		{
			Play_Time += Time::getDeltaTime();

			Krochi::skillState = Krochi::eSkillState::Skill_On;

			Num1 = rand() % 8; // 0~6

			while (Num2 == Num1)
				Num2 = rand() % 8;

			while (Num2 == Num3 || Num1 == Num3)
				Num3 = rand() % 8;
		}
		GameObject::Update();
	}

	//Item_List
	void PlayerManager::speed_up()
	{
		Krochi::vel += 5;
		Skills[(int)eItems::WIND].item_level += 1;

		selected_item = eItems::NONE;
	}
	void PlayerManager::light_up()
	{
		Krochi::Light_Power += 5;
		Skills[(int)eItems::LIGHTNING].item_level += 1;
		selected_item = eItems::NONE;
	}
	void PlayerManager::book_up()
	{
		Krochi::Books_Power += 3;
		Skills[(int)eItems::BOOK].item_level += 1;
		selected_item = eItems::NONE;
	}
	void PlayerManager::power_up()
	{
		Krochi::Light_Power += 2;
		Krochi::Books_Power += 2;
		Skills[(int)eItems::POWER_UP].item_level += 1;
		selected_item = eItems::NONE;
	}
	void PlayerManager::armor_up()
	{
		Krochi::Armor += 0.3f;
		Skills[(int)eItems::ARMOR].item_level += 1;
		selected_item = eItems::NONE;
	}
	void PlayerManager::empty_book()
	{
		Krochi::defaultTime += 0.3f;
		Skills[(int)eItems::EMEPY_BOOK].item_level += 1;
		selected_item = eItems::NONE;
	}
	void PlayerManager::cross_up()
	{
		Krochi::Cross_Power += 5;
		Skills[(int)eItems::CROSS].item_level += 1;
		selected_item = eItems::NONE;
	}
	void PlayerManager::heart_up()
	{
		Krochi::recovery += 0.3f;

		Skills[(int)eItems::HEART].item_level += 1;
		selected_item = eItems::NONE;
	}
	//
	void PlayerManager::Render(HDC hdc)
	{
		Tr->setPos(Krochi::getPlayerPos() + Vector2(8,320)); // Treasure_show 애니메이션 위치

		TransparentBlt(hdc, 152, 5, level_bar->GetWidth(), level_bar->GetHeight(),
			level_bar->GetHdc(), 0, 0, level_bar->GetWidth(), level_bar->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 152, 5, Krochi::Exp, Ex_value->GetHeight(),
			Ex_value->GetHdc(), 0, 0, Krochi::Exp, Ex_value->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 15, 5, Charactor->GetWidth(), Charactor->GetHeight(),
			Charactor->GetHdc(), 0, 0, Charactor->GetWidth(), Charactor->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 152, 39, Item_list->GetWidth() * 2.2 , Item_list->GetHeight() * 2.2 ,
			Item_list->GetHdc(), 0, 0, Item_list->GetWidth(), Item_list->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 22, 120, health_zero->GetWidth(), health_zero->GetHeight(),
			health_zero->GetHdc(), 0, 0, health_zero->GetWidth(), health_zero->GetHeight(), RGB(255, 0, 255));
		TransparentBlt(hdc, 22, 120, Krochi::Hp, health->GetHeight(),
			health->GetHdc(), 0, 0, health->GetWidth(), health->GetHeight(), RGB(255, 0, 255));

		int minute = (int)Play_Time / 60;
		int second = (int)Play_Time % 60;

		std::wstringstream ss;
		ss << std::setfill(L'0') << std::setw(2) << minute << L" : " << std::setfill(L'0') << std::setw(2) << second;

		std::wstring text = ss.str();
		std::wstring text2 = L"LV " + std::to_wstring((int)Krochi::level);

		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		oldfont = (HFONT)SelectObject(hdc, font1);
		TextOut(hdc, 592, 37, text.c_str(), text.length());
		SelectObject(hdc, oldfont);
		oldfont = (HFONT)SelectObject(hdc, font2);
		TextOut(hdc, 1222, 11, text2.c_str(), text2.length());
		SelectObject(hdc, oldfont);

		if (PlayerManager::Show_on)
		{
			TransparentBlt(hdc, 382, 65, Tresure_UI->GetWidth(), Tresure_UI->GetHeight(),
				Tresure_UI->GetHdc(), 0, 0, Tresure_UI->GetWidth(), Tresure_UI->GetHeight(), RGB(255, 0, 255));

			Treasure_show->Play_NO_RE(L"TreasuresShow2", false);

			if (Treasure_show->IsComplete())
			{
				Treasure_show->Play_NO_RE(L"NULL", false);
				PlayerManager::Show_on = false;
				Krochi::mState = Krochi::ePlayerState::Idle;
			}
		}
		if (PlayerManager::Level_Up)
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);

			std::wstring text1 = L"신규 무기!";
			oldfont = (HFONT)SelectObject(hdc, font2);
				
			TransparentBlt(hdc, 382, 65, menuImg->GetWidth(), menuImg->GetHeight(),
				menuImg->GetHdc(), 0, 0, menuImg->GetWidth(), menuImg->GetHeight(), RGB(255, 0, 255));

			TransparentBlt(hdc, 397, 176, Skills[Num1].item_image->GetWidth() * 2, Skills[Num1].item_image->GetHeight() * 2,
				Skills[Num1].item_image->GetHdc(), 0, 0, Skills[Num1].item_image->GetWidth(), Skills[Num1].item_image->GetHeight(), RGB(255, 0, 255));
	
			TransparentBlt(hdc, 397, 305, Skills[Num2].item_image->GetWidth() * 2, Skills[Num2].item_image->GetHeight() * 2,
				Skills[Num2].item_image->GetHdc(), 0, 0, Skills[Num2].item_image->GetWidth(), Skills[Num2].item_image->GetHeight(), RGB(255, 0, 255));

			TransparentBlt(hdc, 397, 434, Skills[Num3].item_image->GetWidth() * 2, Skills[Num3].item_image->GetHeight() * 2,
				Skills[Num3].item_image->GetHdc(), 0, 0, Skills[Num3].item_image->GetWidth(), Skills[Num3].item_image->GetHeight(), RGB(255, 0, 255));

			if(Skills[Num1].item_level == 1)
				TextOut(hdc, 780, 176, text1.c_str(), text1.length());
			else if (Skills[Num1].item_level > 1)
			{
				std::wstring text3 = L"LV " + std::to_wstring(Skills[Num1].item_level);
				TextOut(hdc, 780, 176, text3.c_str(), text3.length());
			}

			if(Skills[Num2].item_level == 1)
				TextOut(hdc, 780, 305, text1.c_str(), text1.length());
			else if (Skills[Num2].item_level > 1)
			{
				std::wstring text4 = L"LV " + std::to_wstring(Skills[Num2].item_level);
				TextOut(hdc, 780, 305, text4.c_str(), text4.length());
			}

			if (Skills[Num3].item_level == 1)
				TextOut(hdc, 780, 434, text1.c_str(), text1.length());
			else if (Skills[Num3].item_level > 1)
			{
				std::wstring text5 = L"LV " + std::to_wstring(Skills[Num3].item_level);
				TextOut(hdc, 780, 434, text5.c_str(), text5.length());
			}

			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				Vector2 mPos = Input::GetMousePos();

				if (mPos.x > 400 && mPos.x < 881
					&& mPos.y > 175 && mPos.y < 288) // 첫번째 칸
				{
					selected_item = (eItems)Num1;
				}
				if (mPos.x > 400 && mPos.x < 881
					&& mPos.y > 304 && mPos.y < 417) // 두번째 칸
				{
					selected_item = (eItems)Num2;
				}
				if (mPos.x > 400 && mPos.x < 881
					&& mPos.y > 436 && mPos.y < 549) // 세번째 칸
				{
					selected_item = (eItems)Num3;
				}

				if (selected_item != eItems::NONE)
				{
					PlayerManager::Level_Up = false;
					Krochi::mState = Krochi::ePlayerState::Idle;
				}
			}
			SelectObject(hdc, oldfont);
		}
		GameObject::Render(hdc);
	}
	void PlayerManager::Release()
	{
		delete[] Skills;
		DeleteObject(font1);
		DeleteObject(font2);
	}
}