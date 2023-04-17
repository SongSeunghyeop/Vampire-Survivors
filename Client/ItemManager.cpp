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
		font1 = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Maplestory");
		font2 = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Maplestory");
		font3 = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Maplestory");
 	}
	ItemManager::~ItemManager()
	{

	}
	void ItemManager::Initialize()
	{	
		Tr = GetComponent<Transform>();

		//�������� ��
		Treasure_show = AddComponent<Animator>();
		Treasure_show->CreateAnimations(L"..\\Resources\\Treasures\\Show2", 0.075f);

		//������ UI, �������� ���� UI
		menuImg = ResourceManager::Load<Image>(L"Option_LevelUp", L"..\\Resources\\Option_LevelUp.bmp");
		Tresure_UI = ResourceManager::Load<Image>(L"Tresure_UI", L"..\\Resources\\Option.bmp");

		//���� ����
		//8
		
		items = new Item_Info[20];

		Item_Num = sizeof(items);
		//Items -> �̹���, ����
		items[(int)eItems::WIND].item_image = ResourceManager::Load<Image>(L"wind", L"..\\Resources\\wind.bmp");
		items[(int)eItems::WIND].item_name = L"����";
		items[(int)eItems::WIND].item_effect = L"������ �̵��ӵ��� ����մϴ�.";
		items[(int)eItems::POWER_UP].item_image = ResourceManager::Load<Image>(L"Power_up", L"..\\Resources\\PowerUp.bmp");
		items[(int)eItems::POWER_UP].item_name = L"�ñ�ġ";
		items[(int)eItems::POWER_UP].item_effect = L"������ ���ݷ��� �����մϴ�.";
		items[(int)eItems::LIGHTNING].item_image = ResourceManager::Load<Image>(L"Lightning_Item", L"..\\Resources\\Lightning_Item.bmp");
		items[(int)eItems::LIGHTNING].item_name = L"���� ����";
		items[(int)eItems::LIGHTNING].item_effect = L"������ ������ ������ ����Ĩ�ϴ�.";
		items[(int)eItems::BOOK].item_image = ResourceManager::Load<Image>(L"Book_Item", L"..\\Resources\\Book_select.bmp");
		items[(int)eItems::BOOK].item_name = L"����";
		items[(int)eItems::BOOK].item_effect = L"�ֺ��� ȸ���ϸ� �����մϴ�.";
		items[(int)eItems::ARMOR].item_image = ResourceManager::Load<Image>(L"Armor", L"..\\Resources\\armor.bmp");
		items[(int)eItems::ARMOR].item_name = L"����";
		items[(int)eItems::ARMOR].item_effect = L"������ ������ �����մϴ�.";
		items[(int)eItems::EMEPY_BOOK].item_image = ResourceManager::Load<Image>(L"EmptyBook", L"..\\Resources\\Empty_Book.bmp");
		items[(int)eItems::EMEPY_BOOK].item_name = L"�� å";
		items[(int)eItems::EMEPY_BOOK].item_effect = L"������ ��Ÿ���� �����մϴ�.";
		items[(int)eItems::CROSS].item_image = ResourceManager::Load<Image>(L"Cross_select", L"..\\Resources\\cross_select.bmp");
		items[(int)eItems::CROSS].item_name = L"���ڰ�";
		items[(int)eItems::CROSS].item_effect = L"��ó�� ������ ���ư��� �θ޶�ó�� ���ƿɴϴ�.";
		items[(int)eItems::HEART].item_image = ResourceManager::Load<Image>(L"Heart", L"..\\Resources\\Heart.bmp");
		items[(int)eItems::HEART].item_name = L"���� ����";
		items[(int)eItems::HEART].item_effect = L"������ �� �� 0.3 �� ü���� ȸ���˴ϴ�.";

		items[(int)eItems::LIGHTNING].item_level = 1;
	
		selected_item = eItems::NONE;

		GameObject::Initialize();
	}
	void ItemManager::Update()
	{	 
		switch (selected_item)
		{ // ������ ���ÿ� ���� �Լ� ����
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
		// ������ Ȥ�� �������� ���� �� ������ ��ų �Ͻ�����
		if (PlaySceneManager::Level_Up || PlaySceneManager::Show_on)
		{

		}
		if (!PlaySceneManager::Level_Up && !PlaySceneManager::Show_on)
		{
			//�������� ������ 8�� �Ǹ� �迭���� �� �ڷ� ������, ������ ���� ���� ����Ʈ���� ����
			
		/*	for (it = items.begin(); it != items.end() ; it++)
			{
				if ((*it)->item_level == 7)
				{
					items.erase(it);
					--Item_Num;
					break;
				}
			}*/

			//������ ������ ����, �����۸���Ʈ�� ������ ���� ���� ����
	
			Num1 = rand() % Item_Num;

			while (Num2 == Num1)
				Num2 = rand() % Item_Num;

			while (Num2 == Num3 || Num1 == Num3)
				Num3 = rand() % Item_Num;
		}

		//�÷���Ÿ���� ���� �ð� ������ �� ���� ����
		if(PlaySceneManager::Play_Time > 120.0f && treasure == NULL)
			treasure = object::Instantiate<Treasure>(eLayerType::ITEMS);

		if (PlaySceneManager::Play_Time > 120.0f && magnet == NULL)
			magnet = object::Instantiate<Magnet>(eLayerType::ITEMS);

		GameObject::Update();
	}

	//������ ���ÿ� ���� �Լ�
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
		Krochi::Books_Power += 3;
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
	//
	void ItemManager::Render(HDC hdc)
	{
		Tr->setPos(Krochi::getPlayerPos() + Vector2(8,320)); // Treasure_show �ִϸ��̼� ��ġ

		//�������� ���� �� 
		if (PlaySceneManager::Show_on)
		{
			TransparentBlt(hdc, 382, 65, Tresure_UI->GetWidth(), Tresure_UI->GetHeight(),
				Tresure_UI->GetHdc(), 0, 0, Tresure_UI->GetWidth(), Tresure_UI->GetHeight(), RGB(255, 0, 255));

			Treasure_show->Play_NO_RE(L"TreasuresShow2", false);

			if (Treasure_show->IsComplete())
			{
				Treasure_show->Play_NO_RE(L"NULL", false);
				PlaySceneManager::Show_on = false;
				Krochi::mState = Krochi::ePlayerState::Idle;
			}
		}
		//���� �� ��
		if (PlaySceneManager::Level_Up)
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);
			oldfont = (HFONT)SelectObject(hdc, font2);
				
			TransparentBlt(hdc, 382, 65, menuImg->GetWidth(), menuImg->GetHeight(),
				menuImg->GetHdc(), 0, 0, menuImg->GetWidth(), menuImg->GetHeight(), RGB(255, 0, 255));

			TransparentBlt(hdc, 397, 176, items[Num1].item_image->GetWidth() * 2, items[Num1].item_image->GetHeight() * 2,
				items[Num1].item_image->GetHdc(), 0, 0, items[Num1].item_image->GetWidth() , items[Num1].item_image->GetHeight(), RGB(255, 0, 255));
	
			TransparentBlt(hdc, 397, 305, items[Num2].item_image->GetWidth() * 2, items[Num2].item_image->GetHeight() * 2,
				items[Num2].item_image->GetHdc(), 0, 0, items[Num2].item_image->GetWidth(), items[Num2].item_image->GetHeight(), RGB(255, 0, 255));

			TransparentBlt(hdc, 397, 434, items[Num3].item_image->GetWidth() * 2, items[Num3].item_image->GetHeight() * 2,
				items[Num3].item_image->GetHdc(), 0, 0, items[Num3].item_image->GetWidth(), items[Num3].item_image->GetHeight(), RGB(255, 0, 255));

				new_item = L"�ű� ����!";
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
				TextOut(hdc, 460, 176, name1.c_str(), name1.length());
				TextOut(hdc, 400, 240, info1.c_str(), info1.length());
				TextOut(hdc, 780, 176, new_item.c_str(), new_item.length());
			}
			else if (items[Num1].item_level > 0)
			{
				TextOut(hdc, 460, 176, name1.c_str(), name1.length());
				TextOut(hdc, 400, 240, info1.c_str(), info1.length());
				TextOut(hdc, 780, 176, num1_LV.c_str(), num1_LV.length());
			}
			if (items[Num2].item_level == 0)
			{
				TextOut(hdc, 460, 305, name2.c_str(), name2.length());
				TextOut(hdc, 400, 369, info2.c_str(), info2.length());
				TextOut(hdc, 780, 305, new_item.c_str(), new_item.length());
			}
			else if (items[Num2].item_level > 0)
			{
				TextOut(hdc, 460, 305, name2.c_str(), name2.length());
				TextOut(hdc, 400, 369, info2.c_str(), info2.length());
				TextOut(hdc, 780, 305, num2_LV.c_str(), num2_LV.length());
			}
			if (items[Num3].item_level == 0)
			{
				TextOut(hdc, 460, 434, name3.c_str(), name3.length());
				TextOut(hdc, 400, 498, info3.c_str(), info3.length());
				TextOut(hdc, 780, 434, new_item.c_str(), new_item.length());
			}
			else if (items[Num3].item_level > 0)
			{
				TextOut(hdc, 460, 434, name3.c_str(), name3.length());
				TextOut(hdc, 400, 498, info3.c_str(), info3.length());
				TextOut(hdc, 780, 434, num3_LV.c_str(), num3_LV.length());
			}

			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				Vector2 mPos = Input::GetMousePos();

				if (mPos.x > 400 && mPos.x < 881
					&& mPos.y > 175 && mPos.y < 288) // ù��° ĭ
				{
					selected_item = (eItems)Num1;
				}
				if (mPos.x > 400 && mPos.x < 881
					&& mPos.y > 304 && mPos.y < 417) // �ι�° ĭ
				{
					selected_item = (eItems)Num2;
				}
				if (mPos.x > 400 && mPos.x < 881
					&& mPos.y > 436 && mPos.y < 549) // ����° ĭ
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
		GameObject::Render(hdc);
	}

	void ItemManager::Release()
	{
		delete[] items;

		DeleteObject(font1);
		DeleteObject(font2);
		DeleteObject(font3);
	}
}