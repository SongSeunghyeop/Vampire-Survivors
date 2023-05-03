#include "ItemManager.h"
#include "myInput.h"
#include "myPlayScene.h"
#include "Treasure.h"
#include "Magnet.h"
#include <algorithm>

namespace my
{
	ItemManager::ItemManager()
	{
		font1 = CreateFont(27, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"돋움체");
		font2 = CreateFont(17, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"돋움체");
 	}
	ItemManager::~ItemManager()
	{

	}
	void ItemManager::Initialize()
	{	
		Tr = GetComponent<Transform>();

		//보물상자 씬
		Treasure_show = AddComponent<Animator>();
		Treasure_show->CreateAnimations(L"..\\Resources\\Treasures\\Show2", 0.075f);

		//레벨업 UI, 보물상자 오픈 UI
		menuImg = ResourceManager::Load<Image>(L"Option_LevelUp", L"..\\Resources\\Option_LevelUp.bmp");
		Tresure_UI = ResourceManager::Load<Image>(L"Tresure_UI", L"..\\Resources\\Option.bmp");
		Item_list = ResourceManager::Load<Image>(L"Item_list", L"..\\Resources\\Item_list.bmp");
		//무기 종류
		//8
		items = new Item_Info[20];

		Item_Num = (int)eItems::NONE;
		//Items -> 이미지, 레벨
		items[(int)eItems::WIND].item_image = ResourceManager::Load<Image>(L"wind", L"..\\Resources\\wind.bmp");
		items[(int)eItems::WIND].item_icon = ResourceManager::Load<Image>(L"wind_icon", L"..\\Resources\\wind_icon.bmp");
		items[(int)eItems::WIND].item_name = L"날개";
		items[(int)eItems::WIND].item_effect = L"레벨당 이동속도가 상승합니다.";
		items[(int)eItems::POWER_UP].item_image = ResourceManager::Load<Image>(L"Power_up", L"..\\Resources\\PowerUp.bmp");
		items[(int)eItems::POWER_UP].item_icon = ResourceManager::Load<Image>(L"Power_up_icon", L"..\\Resources\\PowerUp_icon.bmp");
		items[(int)eItems::POWER_UP].item_name = L"시금치";
		items[(int)eItems::POWER_UP].item_effect = L"레벨당 공격력이 증가합니다.";
		items[(int)eItems::LIGHTNING].item_image = ResourceManager::Load<Image>(L"Lightning_Item", L"..\\Resources\\Lightning_Item.bmp");
		items[(int)eItems::LIGHTNING].item_name = L"번개 반지";
		items[(int)eItems::LIGHTNING].item_effect = L"무작위 적에게 번개를 내려칩니다.";
		items[(int)eItems::BOOK].item_image = ResourceManager::Load<Image>(L"Book_Item", L"..\\Resources\\Book_select.bmp");
		items[(int)eItems::BOOK].item_icon = ResourceManager::Load<Image>(L"book_icon", L"..\\Resources\\book_icon.bmp");
		items[(int)eItems::BOOK].item_name = L"성경";
		items[(int)eItems::BOOK].item_effect = L"주변을 회전하며 공격합니다.";
		items[(int)eItems::ARMOR].item_image = ResourceManager::Load<Image>(L"Armor", L"..\\Resources\\armor.bmp");
		items[(int)eItems::ARMOR].item_icon = ResourceManager::Load<Image>(L"armor_icon", L"..\\Resources\\armor_icon.bmp");
		items[(int)eItems::ARMOR].item_name = L"갑옷";
		items[(int)eItems::ARMOR].item_effect = L"레벨당 방어력이 증가합니다.";
		items[(int)eItems::EMEPY_BOOK].item_image = ResourceManager::Load<Image>(L"EmptyBook", L"..\\Resources\\Empty_Book.bmp");
		items[(int)eItems::EMEPY_BOOK].item_icon = ResourceManager::Load<Image>(L"EmptyBook_icon", L"..\\Resources\\Empty_Book_icon.bmp");
		items[(int)eItems::EMEPY_BOOK].item_name = L"빈 책";
		items[(int)eItems::EMEPY_BOOK].item_effect = L"레벨당 쿨타임이 감소합니다.";
		items[(int)eItems::CROSS].item_image = ResourceManager::Load<Image>(L"Cross_select", L"..\\Resources\\cross_select.bmp");
		items[(int)eItems::CROSS].item_icon = ResourceManager::Load<Image>(L"cross_icon", L"..\\Resources\\cross_icon.bmp");
		items[(int)eItems::CROSS].item_name = L"십자가";
		items[(int)eItems::CROSS].item_effect = L"근처의 적에게 날아가며 부메랑처럼 돌아옵니다.";
		items[(int)eItems::HEART].item_image = ResourceManager::Load<Image>(L"Heart", L"..\\Resources\\Heart.bmp");
		items[(int)eItems::HEART].item_icon = ResourceManager::Load<Image>(L"Heart_icon", L"..\\Resources\\Heart_icon.bmp");
		items[(int)eItems::HEART].item_name = L"붉은 심장";
		items[(int)eItems::HEART].item_effect = L"레벨당 매 초 0.3 의 체력이 회복됩니다.";
		items[(int)eItems::AX1].item_image = ResourceManager::Load<Image>(L"ax1", L"..\\Resources\\ax1_select.bmp");
		items[(int)eItems::AX1].item_image2 = ResourceManager::Load<Image>(L"ax2", L"..\\Resources\\ax2_select.bmp");
		items[(int)eItems::AX1].item_icon = ResourceManager::Load<Image>(L"ax_icon", L"..\\Resources\\ax_icon.bmp");
		items[(int)eItems::AX1].item_icon2 = ResourceManager::Load<Image>(L"ax_icon2", L"..\\Resources\\ax2_icon.bmp");
		items[(int)eItems::AX1].item_name = L"도끼";
		items[(int)eItems::AX1].item_name2 = L"죽음의 나선";
		items[(int)eItems::AX1].item_effect = L"피해량이 높고 공격 범위가 넓습니다.";
		items[(int)eItems::AX1].item_effect2 = L"도끼의 진화형. 적을 관통합니다.";

		items[(int)eItems::LIGHTNING].item_level = 1;

		selected_item = eItems::NONE;

		GameObject::Initialize();
	}
	void ItemManager::Update()
	{	 
		switch (selected_item)
		{ // 아이템 선택에 따른 함수 적용
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
		case(eItems::AX1):
			ax1();
			break;
		}
		// 레벨업 혹은 보물상자 오픈 시 아이템 스킬 일시정지
		if (!PlaySceneManager::Level_Up && !PlaySceneManager::Show_on)
		{
		 //아이템리스트중 랜덤의 숫자 세개 선정
			Num1 = rand() % Item_Num;

			while (Num2 == Num1)
				Num2 = rand() % Item_Num;

			while (Num2 == Num3 || Num1 == Num3)
				Num3 = rand() % Item_Num;
		}

		//플레이타임이 일정 시간 지났을 때 보물 등장
		if(PlaySceneManager::Play_Time > 145.0f && treasure == NULL) // 145
			treasure = object::Instantiate<Treasure>(eLayerType::ITEMS);

		if (PlaySceneManager::Play_Time > 90.0f && magnet == NULL) // 90
			magnet = object::Instantiate<Magnet>(eLayerType::ITEMS);

		for (int i = 1; i < 4; i++)
		{
			if (items[i].item_level > 0 && items[i].inited == false)
			{
				item_order.push_back(items[i].item_icon);
				items[i].inited = true;
			}
		}
		for (int i = 4; i < Item_Num; i++)
		{
			if (items[i].item_level > 0 && items[i].inited == false)
			{
				item_order2.push_back(items[i].item_icon);
				items[i].inited = true;
			}
		}

		if (PlaySceneManager::Show_on)
		{
			for (int i = 0; i < item_order.size(); i++)
			{
				if (item_order[i] == items[(int)eItems::AX1].item_icon)
				{
					item_order[i] = items[(int)eItems::AX1].item_icon2;
				}
			}
		}
		GameObject::Update();
	}

	//아이템 선택에 따른 함수
	void ItemManager::speed_up()
	{
		Krochi::vel += 6;
		items[(int)eItems::WIND].item_level += 1;
		selected_item = eItems::NONE;
	}
	void ItemManager::light_up()
	{
		Krochi::Light_Power += 5;
		items[(int)eItems::LIGHTNING].item_level += 1;
		selected_item = eItems::NONE;
	}
	void ItemManager::book_up()
	{
		Krochi::Books_Power += 5;
		items[(int)eItems::BOOK].item_level += 1;
		selected_item = eItems::NONE;
	}
	void ItemManager::power_up()
	{
		Krochi::spinach += 3.0f;
		items[(int)eItems::POWER_UP].item_level += 1;
		selected_item = eItems::NONE;
	}
	void ItemManager::armor_up()
	{
		Krochi::Armor += 0.3f;
		items[(int)eItems::ARMOR].item_level += 1;
		selected_item = eItems::NONE;
	}	
	void ItemManager::empty_book()
	{
		Krochi::defaultTime += 0.3f;
		items[(int)eItems::EMEPY_BOOK].item_level += 1;
		selected_item = eItems::NONE;
	}
	void ItemManager::cross_up()
	{
		Krochi::Cross_Power += 5;
		items[(int)eItems::CROSS].item_level += 1;
		selected_item = eItems::NONE;
	}
	void ItemManager::heart_up()
	{
		Krochi::recovery += 0.3f;

		items[(int)eItems::HEART].item_level += 1;
		selected_item = eItems::NONE;
	}
	void ItemManager::ax1()
	{
		Krochi::Ax_Power += 5;

		items[(int)eItems::AX1].item_level += 1;
		selected_item = eItems::NONE;
	}
	//
	void ItemManager::Render(HDC hdc)
	{
		Tr->setPos(Krochi::getPlayerPos() + Vector2(10,290)); // Treasure_show 애니메이션 위치

		TransparentBlt(hdc, 152, 39, Item_list->GetWidth() * 2.4, Item_list->GetHeight() * 2.4,
			Item_list->GetHdc(), 0, 0, Item_list->GetWidth(), Item_list->GetHeight(), RGB(255, 0, 255));

		//보물상자 오픈 시 
		if (PlaySceneManager::Show_on)
		{
			items[(int)eItems::AX1].item_image = items[(int)eItems::AX1].item_image2;
			items[(int)eItems::AX1].item_icon = items[(int)eItems::AX1].item_icon2;
			items[(int)eItems::AX1].item_name = items[(int)eItems::AX1].item_name2;
			items[(int)eItems::AX1].item_effect = items[(int)eItems::AX1].item_effect2;

			TransparentBlt(hdc, 391, 70, Tresure_UI->GetWidth(), Tresure_UI->GetHeight(),
				Tresure_UI->GetHdc(), 0, 0, Tresure_UI->GetWidth(), Tresure_UI->GetHeight(), RGB(255, 0, 255));
			
			Treasure_show->Play_NO_RE(L"TreasuresShow2", false);

			if (Treasure_show->IsComplete())
			{
				Treasure_show->Play_NO_RE(L"NULL", false);
				PlaySceneManager::Show_on = false;
				//ResourceManager::Find<Sound>(L"PlayScene_Sound")->Play(true);
				Krochi::mState = Krochi::ePlayerState::Idle;
			}
		}
		//레벨 업 시
		if (PlaySceneManager::Level_Up)
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);
			oldfont = (HFONT)SelectObject(hdc, font2);
				
			TransparentBlt(hdc, 391, 70, menuImg->GetWidth(), menuImg->GetHeight(),
				menuImg->GetHdc(), 0, 0, menuImg->GetWidth(), menuImg->GetHeight(), RGB(255, 0, 255));

			TransparentBlt(hdc, 406, 181, items[Num1].item_image->GetWidth() * 2, items[Num1].item_image->GetHeight() * 2,
				items[Num1].item_image->GetHdc(), 0, 0, items[Num1].item_image->GetWidth() , items[Num1].item_image->GetHeight(), RGB(255, 0, 255));
	
			TransparentBlt(hdc, 406, 310, items[Num2].item_image->GetWidth() * 2, items[Num2].item_image->GetHeight() * 2,
				items[Num2].item_image->GetHdc(), 0, 0, items[Num2].item_image->GetWidth(), items[Num2].item_image->GetHeight(), RGB(255, 0, 255));

			TransparentBlt(hdc, 406, 439, items[Num3].item_image->GetWidth() * 2, items[Num3].item_image->GetHeight() * 2,
				items[Num3].item_image->GetHdc(), 0, 0, items[Num3].item_image->GetWidth(), items[Num3].item_image->GetHeight(), RGB(255, 0, 255));

				new_item = L"신규 무기!";
				name1 = items[Num1].item_name;
				name2 = items[Num2].item_name;
				name3 = items[Num3].item_name;

				info1 = items[Num1].item_effect;
				info2 = items[Num2].item_effect;
				info3 = items[Num3].item_effect;

				num1_LV = L"LV " + std::to_wstring(items[Num1].item_level + 1);
				num2_LV = L"LV " + std::to_wstring(items[Num2].item_level + 1);
				num3_LV = L"LV " + std::to_wstring(items[Num3].item_level + 1);

			if (items[Num1].item_level == 0)
			{
				TextOut(hdc, 469, 181, name1.c_str(), name1.length());
				TextOut(hdc, 409, 245, info1.c_str(), info1.length());
				TextOut(hdc, 789, 181, new_item.c_str(), new_item.length());
			}
			else if (items[Num1].item_level > 0)
			{
				TextOut(hdc, 469, 181, name1.c_str(), name1.length());
				TextOut(hdc, 409, 245, info1.c_str(), info1.length());
				TextOut(hdc, 789, 181, num1_LV.c_str(), num1_LV.length());
			}
			if (items[Num2].item_level == 0)
			{
				TextOut(hdc, 469, 310, name2.c_str(), name2.length());
				TextOut(hdc, 409, 374, info2.c_str(), info2.length());
				TextOut(hdc, 789, 310, new_item.c_str(), new_item.length());
			}
			else if (items[Num2].item_level > 0)
			{
				TextOut(hdc, 469, 310, name2.c_str(), name2.length());
				TextOut(hdc, 409, 374, info2.c_str(), info2.length());
				TextOut(hdc, 789, 310, num2_LV.c_str(), num2_LV.length());
			}
			if (items[Num3].item_level == 0)
			{
				TextOut(hdc, 469, 439, name3.c_str(), name3.length());
				TextOut(hdc, 409, 503, info3.c_str(), info3.length());
				TextOut(hdc, 789, 439, new_item.c_str(), new_item.length());
			}
			else if (items[Num3].item_level > 0)
			{
				TextOut(hdc, 469, 439, name3.c_str(), name3.length());
				TextOut(hdc, 409, 503, info3.c_str(), info3.length());
				TextOut(hdc, 789, 439, num3_LV.c_str(), num3_LV.length());
			}

			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				Vector2 mPos = Input::GetMousePos();

				if (mPos.x > 409 && mPos.x < 890
					&& mPos.y > 180 && mPos.y < 293) // 첫번째 칸
				{
					selected_item = (eItems)Num1;
				}
				if (mPos.x > 409 && mPos.x < 890
					&& mPos.y > 309 && mPos.y < 422) // 두번째 칸
				{
					selected_item = (eItems)Num2;
				}
				if (mPos.x > 409 && mPos.x < 890
					&& mPos.y > 441 && mPos.y < 554) // 세번째 칸
				{
					selected_item = (eItems)Num3;
				}

				if (selected_item != eItems::NONE)
				{
					PlaySceneManager::Level_Up = false;
					Krochi::mState = Krochi::ePlayerState::Idle;
				}
			}
			SelectObject(hdc, oldfont); 
		}

		if (item_order.size() >= 1)
			TransparentBlt(hdc, 195, 40, item_order[0]->GetWidth() * 1.9, item_order[0]->GetHeight() * 1.9,
				item_order[0]->GetHdc(), 0, 0, item_order[0]->GetWidth(), item_order[0]->GetHeight(), RGB(255, 0, 255));
		if (item_order.size() >= 2)
			TransparentBlt(hdc, 233, 40, item_order[1]->GetWidth() * 1.9, item_order[1]->GetHeight() * 1.9,
				item_order[1]->GetHdc(), 0, 0, item_order[1]->GetWidth(), item_order[1]->GetHeight(), RGB(255, 0, 255));
		if (item_order.size() >= 3)
			TransparentBlt(hdc, 271, 40, item_order[2]->GetWidth() * 1.9, item_order[2]->GetHeight() * 1.9,
				item_order[2]->GetHdc(), 0, 0, item_order[2]->GetWidth(), item_order[2]->GetHeight(), RGB(255, 0, 255));

		if (item_order2.size() >= 1)
			TransparentBlt(hdc, 156, 81, item_order2[0]->GetWidth() * 1.9, item_order2[0]->GetHeight() * 1.9,
				item_order2[0]->GetHdc(), 0, 0, item_order2[0]->GetWidth(), item_order2[0]->GetHeight(), RGB(255, 0, 255));
		if (item_order2.size() >= 2)
			TransparentBlt(hdc, 194, 81, item_order2[1]->GetWidth() * 1.9, item_order2[1]->GetHeight() * 1.9,
				item_order2[1]->GetHdc(), 0, 0, item_order2[1]->GetWidth(), item_order2[1]->GetHeight(), RGB(255, 0, 255));
		if (item_order2.size() >= 3)
			TransparentBlt(hdc, 232, 81, item_order2[2]->GetWidth() * 1.9, item_order2[2]->GetHeight() * 1.9,
				item_order2[2]->GetHdc(), 0, 0, item_order2[2]->GetWidth(), item_order2[2]->GetHeight(), RGB(255, 0, 255));
		if (item_order2.size() >= 4)
			TransparentBlt(hdc, 270, 81, item_order2[3]->GetWidth() * 1.9, item_order2[3]->GetHeight() * 1.9,
				item_order2[3]->GetHdc(), 0, 0, item_order2[3]->GetWidth(), item_order2[3]->GetHeight(), RGB(255, 0, 255));
		if (item_order2.size() >= 5)
			TransparentBlt(hdc, 308, 81, item_order2[4]->GetWidth() * 1.9, item_order2[4]->GetHeight() * 1.9,
				item_order2[4]->GetHdc(), 0, 0, item_order2[4]->GetWidth(), item_order2[4]->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void ItemManager::Release()
	{
		delete[] items;

		DeleteObject(font1);
		DeleteObject(font2);
	}
}